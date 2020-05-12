#ifndef FACTORIAL_H
# define FACTORIAL_H

#include <stdint.h>

typedef struct s_factorial_args {
	uint64_t begin;
	uint64_t end;
	uint64_t mod;
}				t_factorial_args;

uint64_t mult_modulo(uint64_t a, uint64_t b, uint64_t mod);
uint64_t factorial(const t_factorial_args *args);

#endif
