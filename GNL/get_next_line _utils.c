
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}
void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	write (fd, s, ft_strlen(s));
	write (fd, "\n", 1);
}
char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr != '\0')
	{
		if (*ptr == (char)c)
		{
			return (ptr);
		}
		ptr++;
	}
	if (c == '\0')
		return (ptr);
	return (NULL);
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	char	*a;
	char	*b;

	a = (char *)s1;
	b = (char *)s2;

	if (n == 0)
	return (0);
	while (n --)
	{
		if (*a != *b)
		{
			return (*a - *b);
		}
		a++;
		b++;
	}
	return (0);
}