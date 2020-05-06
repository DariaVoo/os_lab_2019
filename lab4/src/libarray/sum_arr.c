#include "arraylib.h"

int sum_arr(const t_sum_args *args)
{
	int sum = 0;
	int i = args->begin;

	while (i < args->end)
	{
		sum += args->array[i];
		i++;
	}
	return sum;
}
