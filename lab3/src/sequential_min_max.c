#include <stdio.h>
#include <stdlib.h>

#include "find_min_max.h"
#include "utils.h"

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Usage: %s seed arraysize\n", argv[0]);
    return 1;
  }

  int seed = atoi(argv[1]);
  if (seed <= 0)
  {
    printf("seed is a positive number\n");
    return 1;
  }

  int array_size = atoi(argv[2]);
  if (array_size <= 0)
  {
    printf("array_size is a positive number\n");
    return 1;
  }

  int *array;
  t_min_max min_max;

  array  = (int *)malloc(array_size * sizeof(int));
  generate_array(array, array_size, seed);
  min_max = get_min_max(array, 0, array_size);
  free(array);

  printf("min: %d\n", min_max.min);
  printf("max: %d\n", min_max.max);

  return 0;
}
