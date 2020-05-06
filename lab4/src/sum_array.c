#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <getopt.h>

#include "arraylib.h"

void *thread_sum(void *args) {
	t_sum_args *sum_args = (t_sum_args *)args;
	return (void *)(size_t)sum_arr(sum_args);
}

int parse(int argc, char **argv, uint32_t *threads_num, uint32_t *array_size, uint32_t *seed)
{
	char *usage = "Usage: %s --threads_num \"num\" --seed \"num\" --array_size \"num\"\n";
	int buf;

	while (1)
	{
		/*optid - индекс следующего элемента, который будет отсканирован*/
		static struct option options[] = {
				{"threads_num", required_argument, 0, 0},
				{"seed", required_argument, 0, 0},
				{"array_size", required_argument, 0, 0},
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
						buf = (uint32_t)atoi(optarg);
						if (buf <= 0)
						{
							printf("threads_num is a positive number\n");
							return 1;
						}
						*threads_num = buf;
						break;
					case 1:
						buf = (uint32_t)atoi(optarg);
						if (buf <= 0)
						{
							printf("seed must be a positive number\n");
							return 1;
						}
						*seed = buf;
						break;
					case 2:
						buf = (uint32_t)atoi(optarg);
						if (buf <= 0)
						{
							printf("array_size must be a positive number\n");
							return 1;
						}
						*array_size = buf;
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
	if (*seed == 0 || *array_size == 0 || *threads_num == 0) {
		printf(usage, argv[0]);
		return 1;
	}
	return 0;
}

int main(int argc, char **argv) {
	/*
	 *  TODO:
	 *  threads_num by command line arguments
	 *  array_size by command line arguments
	 *	seed by command line arguments
	 */
	uint32_t threads_num = 0;
	uint32_t array_size = 0;
	uint32_t seed = 0;
	pthread_t threads[threads_num];

	if (parse(argc, argv, &threads_num, &array_size, &seed))
		return (1);
	else
		printf("%d %d %d\n", threads_num, seed, array_size);
	return (0);
}
/*
	/*
	 * TODO:
	 * your code here
	 * Generate array here
	 *

	int *array = malloc(sizeof(int) * array_size);

	t_sum_args args[threads_num];
	for (uint32_t i = 0; i < threads_num; i++) {
		if (pthread_create(&threads[i], NULL, thread_sum, (void *) &args)) {
			printf("Error: pthread_create failed!\n");
			return 1;
		}
	}

	int total_sum = 0;
	for (uint32_t i = 0; i < threads_num; i++) {
		int sum = 0;
		pthread_join(threads[i], (void **)&sum);
		total_sum += sum;
	}

	free(array);
	printf("Total: %d\n", total_sum);
	return 0;
}
*/