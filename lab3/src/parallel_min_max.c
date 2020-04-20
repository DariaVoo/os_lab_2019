#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <getopt.h>

#include "find_min_max.h"
#include "utils.h"

int main(int argc, char **argv)
{
	int seed = -1;
	int array_size = -1;
	int pnum = -1;
	int timeout = 0;
	bool with_files = false;

	char *usage = "Usage: %s --seed \"num\" --array_size \"num\" --pnum \"num\" --timeout \"num\"(optional --by_files)\n";

	/*-------------------------------
	*---------- Парсинг -------------
	* -------------------------------*/
//  int current_optind;
	while (true)
	{
		/*optid - индекс следующего элемента, который будет отсканирован*/
//    current_optind = optind ? optind : 1;

		static struct option options[] = {
				{"seed", required_argument, 0, 0},
				{"array_size", required_argument, 0, 0},
				{"pnum", required_argument, 0, 0},
				{"timeout", required_argument, 0, 0},
				{"by_files", no_argument, 0, 'f'},
				//для однозначного определения конца массива
				{0, 0, 0, 0}};

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
						seed = atoi(optarg);
						if (seed <= 0)
						{
							printf("seed must be a positive number\n");
							return 1;
						}
						break;
					case 1:
						array_size = atoi(optarg);
						if (array_size <= 0)
						{
							printf("array_size must be a positive number\n");
							return 1;
						}
						break;
					case 2:
						pnum = atoi(optarg);
						if (pnum <= 0)
						{
							printf("pnum is a positive number\n");
							return 1;
						}
						break;
					case 3:
						timeout = atoi(optarg);
						if (timeout < 0)
						{
							printf("timeout is a positive number\n");
							return 1;
						}
						break;
					case 4:
						with_files = true;
						break;

					//defalut:
					//	printf("Index %d is out of options\n", option_index);
				}
				break;
			case 'f':
				with_files = true;
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
	if (seed == -1 || array_size == -1 || pnum == -1) {
		printf(usage, argv[0]);
		return 1;
	}

//  printf("seed %d\narray_size %d\npnum %d\n", seed, array_size, pnum);

	/*-------------------------------
	* ------- Начинаем работу -------
	* -------------------------------*/
	int *array = malloc(sizeof(int) * array_size);
	generate_array(array, array_size, seed);
	int active_child_processes = 0;

	struct timeval start_time;
	gettimeofday(&start_time, NULL);

	/** Вычисляем min max для каждого участка
	 * в соответссвующем процессе
	 * и записываем в файлы результы
	 * */
	/*Количество элементов на которое мы разделяем массив*/
	int			count_num;
	/*Индексы начала и конца поиска*/
	int start = 0;
	int end = 0;
	/*Массив для каналов pipe*/
	int fd[2];

	count_num = array_size / pnum;
	/**Создаём pipe*/
	if (pipe(fd) < 0)
	{
		printf("Can't create pipe\n");
		exit(-1);
	}
	for (int i = 0; i < pnum; i++)
	{
		pid_t child_pid = fork();
		if (child_pid >= 0)
		{
			printf("child_pid %d\n", child_pid);
			// successful fork
			active_child_processes += 1;
			if (child_pid == 0)
			{
				// child process
				t_min_max	child_buf;

				start = count_num * (active_child_processes - 1);
				end = count_num * active_child_processes - 1;
				child_buf = get_min_max(array, start, end);
				// parallel somehow
				if (with_files)
				{
					// use files here
					char *file_name;
					FILE *fp;

					file_name = ft_itoa(active_child_processes);
					/**Открываем файл*/
					if ((fp = fopen(file_name, "w")) == NULL)
					{
						printf("Can't open file %s\n", file_name);
						exit(1);
					}
					/**Записываем в файл max и min*/
					fprintf(fp, "%d\n%d\n", child_buf.max, child_buf.min);
					/**Закрываем файл*/
					if (fclose(fp) != 0)
						printf("File %s don't close!", file_name);

					/**Завершаем процесс*/
					exit(EXIT_SUCCESS);
				} else {
					// use pipe here
					/**Закрываем конец канала для чтения*/
					close(fd[0]);
					char *max, *min;

					max = ft_itoa(child_buf.max);
					min = ft_itoa(child_buf.min);

					/**Записываем в pipe max min*/
					write(fd[1], max, strlen(max));
					write(fd[1], " ", 1);
					write(fd[1], min, strlen(min));
					write(fd[1], "\n", 1);
					/**Закрываем конец канала для записи*/
					close(fd[1]);
					exit(1);
				}
			}
//      else
//      	wait(NULL);
		} else {
			printf("Fork failed!\n");
			return 1;
		}
	}

	while (active_child_processes > 0)
	{
		wait(NULL);
		active_child_processes -= 1;
	}

	t_min_max min_max;
	min_max.min = INT_MAX;
	min_max.max = INT_MIN;

	/**Входной поток данных(для записи) не понадобится, поэтому закрываем его*/
	close(fd[1]);
	for (int i = 1; i <= pnum; i++)
	{
		write(0, "Read\t", 5);
		int min = INT_MAX;
		int max = INT_MIN;

		if (with_files)
		{
			/** Считываем из файлов min max
			 * и ищем наименьшее и наибольшее значение
			 * из всех найденных min max
			 **/
			// read from files
			char *file_name;
			FILE *fp;

			file_name = ft_itoa(i);
			printf("file name: %s\n", file_name);
			if ((fp = fopen(file_name, "r"))== NULL)
			{
				printf("Can't open file %s\n", file_name);
				exit(1);
			}
			/**Считываем min max из файла*/
			fscanf(fp, "%i\n%i\n", &max, &min);
			printf("max %d\tmin %d\n", max, min);
			if (fclose(fp) != 0)
				printf("File %s don't close!", file_name);
			free(file_name);

		} else {
			// read from pipes
			char	*str, *istr;
			char	sep[10] = " ";


			if (get_next_line(fd[0], &str) < 0)
				break ;
			istr = strtok(str, sep);
			if (istr != NULL) {
				max = atoi((const char*)istr);
				min = atoi((const char*)strtok(NULL, sep));
			}
			free(str);
		}

		/**Сравниваем считанные min max с глобальными значениями*/
		if (min < min_max.min) min_max.min = min;
		if (max > min_max.max) min_max.max = max;
	}
	/**Закрываем выходной поток*/
	close(fd[0]);

	struct timeval finish_time;
	gettimeofday(&finish_time, NULL);

	double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
	elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

	free(array);

	printf("Min: %d\n", min_max.min);
	printf("Max: %d\n", min_max.max);
	printf("Elapsed time: %fms\n", elapsed_time);
	fflush(NULL);
	return 0;
}
