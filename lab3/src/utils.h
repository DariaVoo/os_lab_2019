#ifndef UTILS_H
# define UTILS_H

typedef struct s_min_max
{
  int min;
  int max;
}	t_min_max;

void generate_array(int *array, unsigned int array_size, unsigned int seed);

#endif
