#ifndef UTILS_H
# define UTILS_H

typedef struct s_min_max
{
  int min;
  int max;
}	t_min_max;

void	generate_array(int *array, unsigned int array_size, unsigned int seed);
void	print_arr(int *arr, int size);

char	*ft_itoa(int n);
int		get_next_line(const int fd, char **line);
#endif
