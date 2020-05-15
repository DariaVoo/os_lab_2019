#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <factorial.h>
#include <fcntl.h>
#include <pthread.h>

struct Server {
	char	ip[255];
	int		port;
};

typedef struct s_comm {
	int sck;
	t_factorial_args *fac;
}				t_comm;

bool ConvertStringToUI64(const char *str, uint64_t *val)
{
	char *end = NULL;
	unsigned long long i = strtoull(str, &end, 10);
	if (errno == ERANGE) {
		fprintf(stderr, "Out of uint64_t range: %s\n", str);
		return false;
	}

	if (errno != 0)
		return false;

	*val = i;
	return true;
}

int parse_cl(int argc, char **argv, uint64_t *k, uint64_t *mod, char servers[][255])
{
	while (true) {
		static struct option options[] = {{"k", required_argument, 0, 0},
										  {"mod", required_argument, 0, 0},
										  {"servers", required_argument, 0, 0},
										  {0, 0, 0, 0}};

		int option_index = 0;
		int c = getopt_long(argc, argv, "", options, &option_index);

		if (c == -1)
			break;

		switch (c)
		{
			case 0: {
				switch (option_index)
				{
					case 0:
						ConvertStringToUI64(optarg, k);
						if (*k <= 0)
						{
							printf("k must be a positive number\n");
							return 1;
						}
						break;
					case 1:
						ConvertStringToUI64(optarg, mod);
						if (*mod <= 0)
						{
							printf("mod must be a positive number\n");
							return 1;
						}
						break;
					case 2:
						memcpy(servers, optarg, strlen(optarg));
						break;
					default:
						printf("Index %d is out of options\n", option_index);
				}
			} break;

			case '?':
				printf("Arguments error\n");
				break;
			default:
				fprintf(stderr, "getopt returned character code 0%o?\n", c);
		}
	}

	if (*k == 0 || *mod == 0 || !strlen(*servers)) {
		fprintf(stderr, "Using: %s --k 1000 --mod 5 --servers /path/to/file\n",
				argv[0]);
		return 1;
	}
	return (0);
}


void *thread_response(void *args)
{
	t_comm *fargs = (t_comm *)args;

	char task[sizeof(uint64_t) * 3];
	memcpy(task, &(fargs->fac->begin), sizeof(uint64_t));
	memcpy(task + sizeof(uint64_t), &(fargs->fac->end), sizeof(uint64_t));
	memcpy(task + 2 * sizeof(uint64_t), &(fargs->fac->mod), sizeof(uint64_t));
	/*отправляем серверу запрос*/
	if (send(fargs->sck, task, sizeof(task), 0) < 0) {
		fprintf(stderr, "Send failed\n");
		exit(1);
	}
	/*получаем от сервера ответ*/
	char response[sizeof(uint64_t)];
	if (recv(fargs->sck, response, sizeof(response), 0) < 0) {
		fprintf(stderr, "Recieve failed\n");
		exit(1);
	}

	// unite results
	uint64_t res = 0;
	memcpy(&res, response, sizeof(uint64_t));
	printf("ans: %lu\n", res);

	close(fargs->sck);
	return (void *)(uint64_t *)res;
}

int main(int argc, char **argv)
{
	uint64_t k = 0;
	uint64_t mod = 0;
	char servers[255] = {'\0'}; /* 255 - max path len*/
	unsigned int	i; /* счётчик*/
	int				fd; /* дескриптор для списка серверов*/

	if (parse_cl(argc, argv, &k, &mod, &servers))
		return (1);

	unsigned int servers_num = 3;
	struct Server *to = malloc(sizeof(struct Server) * servers_num);

	if ((fd = open(servers, O_RDONLY)) == -1)
	{
		printf("Can't open file %s\n", servers);
		exit(1);
	}

	i = 0;
	/*Считаем доступные нам сервера*/
	while (i < servers_num)
	{
		/*Считываем ip и порт из файла*/
		char	*str, *istr;
		char *ip;
		char	sep[10] = ":";

		if (get_next_line(fd, &str) < 0)
			break ;
		istr = strtok(str, sep);
		if (istr != NULL) {
			ip = istr;
			memcpy(to[i].ip, ip, strlen(ip));
			to[i].port = atoi((const char*)strtok(NULL, sep));
		}
		free(str);
		printf("ip %s\tport %i\n", to[i].ip, to[i].port);
		i++;
	}
	if (close(fd) == -1)
		printf("File %s don't close!", servers);


	int count_num =  k / servers_num;
	pthread_t threads[servers_num];
	for (i = 0; i < servers_num; i++) {
		/*получаем хост по текущиму ip*/
		struct hostent *hostname = gethostbyname(to[i].ip);
		if (hostname == NULL) {
			fprintf(stderr, "gethostbyname failed with %s\n", to[i].ip);
			exit(1);
		}

		/*создаём сокет*/
		struct sockaddr_in server;
		server.sin_family = AF_INET;
		/*не забываем приводить порт и адрес к Network Byte Order*/
		server.sin_port = htons(to[i].port); //16bit port
		server.sin_addr.s_addr = *((unsigned long *)hostname->h_addr); //32bit IP

		/*создаём дескриптор сокета с IPv4 protocols(AD_INET), и протокол по умолчанию(0) для IPv4*/
		int sck = socket(AF_INET, SOCK_STREAM, 0);
		if (sck < 0) {
			fprintf(stderr, "Socket creation failed!\n");
			exit(1);
		}
		/*подключаемся к серверу*/
		if (connect(sck, (struct sockaddr *)&server, sizeof(server)) < 0) {
			fprintf(stderr, "Connection failed\n");
			exit(1);
		}

		// parallel between servers
		t_comm comm;
		comm.sck = sck;
		comm.fac->begin = count_num * i;
		comm.fac->end = count_num * (i + 1) + 1;
		comm.fac->mod = mod;

		if (pthread_create(&threads[i], NULL, thread_response,
						   (void *) &comm)) {
			printf("Error: pthread_create failed!\n");
			return 1;
		}
	}

	uint64_t total = 1;
	uint64_t result;
	// unite results
	for (i = 0; i < servers_num; i++) {
		result = 0;
		pthread_join(threads[i], (void **)&result);

		total = mult_modulo(total, result, mod);
	}
	fprintf(stdout, "answer: %lu\n", total);
	free(to);
	return 0;
}
