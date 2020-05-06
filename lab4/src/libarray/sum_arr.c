#include "arraylib.h"

int sum_arr(const t_sum_args *args)
{
	int sum = 0;
	printf("args begin %d end %d\n", args->begin, args->end);
	int i = args->begin;

	while (i < args->end)
	{
		sum += args->array[i];
		i++;
	}
	return sum;
}
