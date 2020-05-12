#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define FD_MAX 50
#define BUFF_SIZE 50

#include "factorial.h"

static char	*ft_strnew(size_t size)
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

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ans;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = strlen((char *)s1) + strlen((char *)s2);
	ans = ft_strnew(len);
	if (!ans)
		return (NULL);
	ans = strcat(ans, s1);
	ans = strcat(ans, s2);
	ans[len] = '\0';
	return (ans);
}

static char	*ft_del_line(char *s)
{
	char	*buf;

	buf = strchr(s, '\n');
	if (!buf)
		return (NULL);
	buf++;
	buf = strdup(buf);
	if (buf)
	{
		free(s);
		s = NULL;
		return (buf);
	}
	return (NULL);
}

static char	*ft_first_str(char *dst)
{
	size_t	i;
	char	*buf;

	i = 0;
	if (!*dst)
		return (NULL);
	while (dst[i] != '\0' && dst[i] != '\n')
		i++;
	buf = ft_strnew(i);
	if (!buf)
		return (NULL);
	strncpy(buf, dst, i);
	return (buf);
}

int			get_next_line(const int fd, char **line)
{
	int			rd;
	static char	*descriptors[FD_MAX];
	char		buf[BUFF_SIZE + 1];
	char		*tmp;

	if (fd < 0 || !line || fd > FD_MAX)
		return (-1);
	if (!descriptors[fd])
		descriptors[fd] = ft_strnew(1);
	while (!strchr(descriptors[fd], '\n')
		   && (rd = read(fd, buf, BUFF_SIZE)) != 0)
	{
		if (rd < 0)
			return (-1);
		buf[rd] = '\0';
		tmp = ft_strjoin(descriptors[fd], buf);
		free(descriptors[fd]);
		descriptors[fd] = tmp;
	}
	*line = ft_first_str(descriptors[fd]);
	if (!*line && rd == 0)
		return (0);
	descriptors[fd] = ft_del_line(descriptors[fd]);
	return (1);
}