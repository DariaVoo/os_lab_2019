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

struct Server {
	char ip[255];
	int port;
};

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
						// TODO: your code here
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

int main(int argc, char **argv)
{
	uint64_t k = 0;
	uint64_t mod = 0;
	char servers[255] = {'\0'}; // TODO: explain why 255
	unsigned int i; /*счётчик*/
	int fd; /*дескриптор для списка серверов*/

	if (parse_cl(argc, argv, &k, &mod, &servers))
		return (1);

	unsigned int servers_num = 5;
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


	// TODO: work continiously, rewrite to make parallel
	int count_num =  k / servers_num;
	uint64_t answer = 0;
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
		uint64_t begin = count_num * i;
		uint64_t end = count_num * (i + 1) + 1;

		char task[sizeof(uint64_t) * 3];
		memcpy(task, &begin, sizeof(uint64_t));
		memcpy(task + sizeof(uint64_t), &end, sizeof(uint64_t));
		memcpy(task + 2 * sizeof(uint64_t), &mod, sizeof(uint64_t));
		/*отправляем серверу запрос*/
		if (send(sck, task, sizeof(task), 0) < 0) {
			fprintf(stderr, "Send failed\n");
			exit(1);
		}
		/*получаем от сервера ответ*/
		char response[sizeof(uint64_t)];
		if (recv(sck, response, sizeof(response), 0) < 0) {
			fprintf(stderr, "Recieve failed\n");
			exit(1);
		}

		// unite results
		uint64_t res = 0;
		memcpy(&res, response, sizeof(uint64_t));
		answer = mult_modulo(answer, res, mod);
		printf("answer: %lu\n", answer);

		close(sck);
	}
	free(to);

	return 0;
}
