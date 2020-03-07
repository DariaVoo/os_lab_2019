#include "revert_string.h"

void RevertString(char *str)
{
	size_t	len;
	size_t	first;
	size_t	middle;
	char	buf;

	first = 0;
	len = ft_strlen(str) - 1;
	middle = len / 2 + len % 2;
	while (first != middle)
	{
		buf = str[first];
		str[first] = str[len];
		str[len] = buf;
		first++;
		len--;
	}
	return ;
}

