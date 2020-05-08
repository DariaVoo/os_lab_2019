#ifndef FACTORIAL_H
# define FACTORIAL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <getopt.h>

typedef struct	s_factorial {
	int p;
	int begin;
	int end;
}				t_factorial;

#endif
