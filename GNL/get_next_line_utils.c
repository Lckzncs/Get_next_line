/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line _utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludo-nas <ludo-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:16:01 by ludo-nas          #+#    #+#             */
/*   Updated: 2024/11/05 19:16:03 by ludo-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*z;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		z = malloc(1);
		if (z == NULL)
			return (NULL);
		z[0] = '\0';
		return (z);
	}
	if (len > s_len - start)
	{
		len = s_len - start;
	}
	z = malloc(len + 1);
	if (z == NULL)
		return (NULL);
	ft_strlcpy(z, (s + start), (len + 1));
	return (z);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*z;
	size_t	s_len;
	size_t	s_len2;

	if ((char *)s1 == NULL || (char *)s2 == NULL)
	{
		return (NULL);
	}
	s_len = ft_strlen(s1);
	s_len2 = ft_strlen(s2);
	z = malloc(s_len + s_len2 + 1);
	if (z == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(z, s1, s_len +1);
	ft_strlcpy(z + s_len, s2, s_len2 +1);
	z[s_len + s_len2] = '\0';
	return (z);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		len;
	char		*d;
	const char	*s;

	s = src;
	len = 0;
	d = dst;
	if (size > 0)
	{
		while (*s && len < size - 1)
		{
			*d++ = *s;
			s++;
			len++;
		}
		*d = '\0';
	}
	return (ft_strlen(src));
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
