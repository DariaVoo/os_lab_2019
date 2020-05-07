#include "factorial.h"

int parse(int argc, char **argv, int *k, int *pnum, int *mod)
{
	char *usage = "Usage: %s -k \"num\" --pnum \"num\" --mod \"num\"\n";

	while (1)
	{
		/*optid - индекс следующего элемента, который будет отсканирован*/
		static struct option options[] = {
				{"k", required_argument, 0, 'k'},
				{"pnum", required_argument, 0, 0},
				{"mod", required_argument, 0, 0},
				//для однозначного определения конца массива
				{0, 0, 0, 0}
		};
		/*Указатель на переменную, в которую будет помещён
		  индекс текущего параметра из массива options*/
		int option_index = 0;
		/*Парсим параметры*/
		int c = getopt_long(argc, argv, "f", options, &option_index);
		if (c == -1)
			break;
		switch (c)
		{
			case 0:
				switch (option_index)
				{
					case 0:
						*k = atoi(optarg);
						break;
					case 1:
						*pnum = atoi(optarg);
						if (*pnum <= 0)
						{
							printf("pnum must be a positive number\n");
							return 1;
						}
						break;
					case 2:
						*mod = atoi(optarg);
						if (*mod <= 0)
						{
							printf("mod must be a positive number\n");
							return 1;
						}
						break;
				}
				break;

			case '?':
				break;

			default:
				printf("getopt returned character code 0%o?\n", c);
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

int main(int argc, char **argv) {
	int threads_num = 0;
	int array_size = 0;
	int seed = 0;

	if (parse(argc, argv, &threads_num, &array_size, &seed))
		return (1);
	else
		printf("%d %d %d\n", threads_num, seed, array_size);
	return (0);
}