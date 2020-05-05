#include <stdlib.h>

void generate_array(int *array, unsigned int array_size, unsigned int seed)
{
  unsigned int i;
  //srand() используется для установки начала последовательности,
  //генерируемой функцией rand()
  srand(seed);
  i = 0;
  while (i < array_size)
  {
    array[i] = rand();
    i++;
  }
}
