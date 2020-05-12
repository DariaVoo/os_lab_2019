#include "factorial.h"

uint64_t factorial(const t_factorial_args *args)
{
	uint64_t ans = 1;

	//wtf
	ans = mult_modulo(args->begin, args->end, args->mod);
	return ans;
}
