/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:58:49 by snorcros          #+#    #+#             */
/*   Updated: 2019/09/12 20:51:50 by snorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <string.h>

static char		*ft_strdup(const char *src)
{
	char	*ans;
	int		len;

	len = strlen(src);
	ans = (char*)malloc(sizeof(char) * (len + 1));
	if (ans == NULL)
		return (0);
	ans = strcpy(ans, src);
	return (ans);
}

static char		*ft_strnew(size_t size)
{
	char	*ans;

	if (!(size + 1))
		return (NULL);
	ans = (char *)malloc(sizeof(char) * (size + 1));
	if (!ans)
		return (NULL);
	ans = memset(ans, '\0', size + 1);
	return (ans);
}

static int		ft_count_digits(int n)
{
	int	count;
	int buf;

	buf = n;
	count = 0;
	if (n <= 0)
	{
		buf *= -1;
		count++;
	}
	while (buf > 0)
	{
		buf /= 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	char	*str_n;
	int		count;
	size_t	i;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	count = ft_count_digits(n);
	str_n = ft_strnew(count);
	if (!str_n)
		return (NULL);
	if (n < 0)
	{
		str_n[0] = '-';
		n *= -1;
	}
	i = count - 1;
	if (n == 0)
		str_n[i] = 0 + 48;
	while (n > 0)
	{
		str_n[i--] = n % 10 + 48;
		n /= 10;
	}
	return (str_n);
}
