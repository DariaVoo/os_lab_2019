#include <zconf.h>
#include "factorial.h"

/*Общая глобальная переменная факториал*/
int factorial_mod = 1;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

int parse(int argc, char **argv, int *k, int *pnum, int *mod)
{
	char *usage = "Usage: %s -k \"num\" --pnum=\"num\" --mod=\"num\"\n";

	while (1)
	{
		/*optid - индекс следующего элемента, который будет отсканирован*/
		static struct option options[] = {
//				{"k", required_argument, 0, 'k'},
				{"pnum", required_argument, 0, 0},
				{"mod", required_argument, 0, 0},
				//для однозначного определения конца массива
				{0, 0, 0, 0}
		};
		/*Указатель на переменную, в которую будет помещён
		  индекс текущего параметра из массива options*/
		int longindex = 0;
		/*Парсим параметры*/
		int c = getopt_long(argc, argv, "k:", options, &longindex);
		if (c == -1)
			break;
		switch (c)
		{
			case 0:
				switch (longindex)
				{
					case 0:
						*pnum = atoi(optarg);
						if (*pnum <= 0)
						{
							printf("pnum must be a positive number\n");
							return 1;
						}
						break;
					case 1:
						*mod = atoi(optarg);
						if (*mod <= 0)
						{
							printf("mod must be a positive number\n");
							return 1;
						}
						break;
				}
				break;

			case 'k':
				*k = atoi(optarg);
				break;

			case '?':
				break;

			default:
				printf("getopt returned character code 0%o(%c)?\n", c, c);
		}
	}
	if (optind < argc) {
		printf("Has at least one no option argument\n");
		return 1;
	}
	if (*pnum == 0 || *mod == 0) {
		printf(usage, argv[0]);
		return 1;
	}
	return 0;
}

int factmod(t_factorial *fac)
{
	int buf;
	int res = 1;
	int i = fac->begin + 1;

//	printf("begin %d end %d mod %d\n", fac->begin, fac->end, fac->p);
	while (i < fac->end)
	{
		buf =  i % fac->p;
		if (buf != 0)
			res *= buf;
		i++;
	}
	printf("after res %d\n", res);
	pthread_mutex_lock(&mut);
	factorial_mod *= res;
	pthread_mutex_unlock(&mut);
	return res;
}

void *thread_factmod(void *args)
{
	t_factorial *f;

	f = (t_factorial *)args;
	return (void *)(size_t)factmod(f);
}

int main(int argc, char **argv) {
	int k = 0;
	int pnum = 0;
	int mod = 0;

	if (parse(argc, argv, &k, &pnum, &mod))
		return (1);

	int i = 0;
	pthread_t threads[pnum];
	t_factorial args[pnum];
	int count_num = k / pnum;

	while (i < pnum)
	{
		args[i].begin = count_num * i;
		args[i].end = count_num * (i + 1) + 1;
		args[i].p = mod;
		/* Создаём новый поток*/
		if (pthread_create(&threads[i], NULL, thread_factmod, (void *) &args[i])) {
			printf("Error: pthread_create failed!\n");
			return 1;
		}
		i++;
	}

	/*Подождём пока завершаться все потоки*/
	i = 0;
	while (i < pnum)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	printf("Result %d\n", factorial_mod);

	return (0);
}