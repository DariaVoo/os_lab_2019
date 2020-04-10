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
  bool with_files = false;

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
			  if (array_size <= 0)
			  {
			  	printf("pnum is a positive number\n");
			  	return 1;
			  }
            break;
          case 3:
            with_files = true;
            break;

//          defalut:
//            printf("Index %d is out of options\n", option_index);
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
    printf("Usage: %s --seed \"num\" --array_size \"num\" --pnum \"num\" \n",
           argv[0]);
    return 1;
  }

  printf("seed %d\narray_size %d\npnum %d\n", seed, array_size, pnum);

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
  int *status_proc = NULL;

  /**Количество отрезков на которое мы разделяем массив*/
  int			count_num;
  /**Индексы начала и конца поиска*/
  int start = 0;
  int end = 0;

  count_num = array_size / pnum;
  for (int i = 0; i < pnum; i++)
  {
    pid_t child_pid = fork();
    if (child_pid >= 0)
    {
    	printf("child_pid %d\n", child_pid);
//    	write(0, "here\n", 5);
      // successful fork
      active_child_processes += 1;
      if (child_pid == 0)
      {
      	// child process
        t_min_max	child_buf;

        printf("active child process %d\n", active_child_processes);

        start = count_num * (active_child_processes - 1);
        end = count_num * active_child_processes - 1;
        printf("start %d\t end %d\n", start, end);
        child_buf = get_min_max(array, start, end);
        // parallel somehow
        if (with_files)
        {
			write(0, "File\n", 5);
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

			write(0, "EXIT\n", 5);
			/**Завершаем процесс*/
			exit(EXIT_SUCCESS);
        } else {
          // use pipe here
        }
        return 0;
      }
      else
      	wait(status_proc);
    }
    else
	{
      printf("Fork failed!\n");
      return 1;
    }
  }

  while (active_child_processes > 0)
  {
    // your code here
//    wait();
    active_child_processes -= 1;
  }

  t_min_max min_max;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;

  /** Считываем из файлов min max
   * и ищем наименьшее и наибольшее значение
   * из всех найденных min max
   **/
  for (int i = 1; i <= pnum; i++)
  {
  	write(0, "Read\t", 5);
    int min = INT_MAX;
    int max = INT_MIN;

    if (with_files)
    {
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
    }

    /**Сравниваем считанные min max с глобальными значениями*/
    if (min < min_max.min) min_max.min = min;
    if (max > min_max.max) min_max.max = max;
  }

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
