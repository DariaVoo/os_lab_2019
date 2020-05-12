#include <stdio.h>
#include "factorial.h"

uint64_t factorial(const t_factorial_args *args)
{
	uint64_t ans = 1;
	uint64_t buf;
	uint64_t i = args->begin + 1;

	while (i < args->end)
	{
		buf =  i % args->mod;
		if (buf != 0)
		{
			ans *= buf;
			ans = ans % args->mod;
		}
		i++;
	}

	return ans;
}
