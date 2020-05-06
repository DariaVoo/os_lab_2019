#ifndef ARRAYLIB_H
# define ARRAYLIB_H

#include <stdio.h>
#include <stdlib.h>

typedef struct	s_sum_args {
	int *array;
	int begin;
	int end;
}				t_sum_args;

int		sum_arr(const t_sum_args *args);
void	generate_array(int *array, unsigned int array_size, unsigned int seed);
void	print_arr(int *arr, int size);

#endif
