/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludo-nas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:52:38 by ludo-nas          #+#    #+#             */
/*   Updated: 2024/11/29 18:40:09 by ludo-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;
	size_t	i;

	total_size = count * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

static	char	*ft_append_and_free(char *line, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(line, buffer);
	free(line);
	return (temp);
}

static	char	*read_line(int fd, char *line)
{
	char	*buffer;
	ssize_t	bytes_read;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(line, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			if (*line)
				return (line);
			free(line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		line = ft_append_and_free(line, buffer);
	}
	free(buffer);
	return (line);
}

static	char	*process_remainder(char *line)
{
	char	*newline_pos;
	char	*remainder;
	size_t	len;

	remainder = NULL;
	newline_pos = ft_strchr(line, '\n');
	if (newline_pos)
	{
		len = newline_pos - line + 1;
		remainder = ft_substr(line, len, ft_strlen(line) - len);
		line[len] = '\0';
	}
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (remainder)
	{
		line = ft_strjoin(remainder, "");
		free(remainder);
		remainder = NULL;
	}
	else
	{
		line = ft_calloc(1, 1);
	}
	line = read_line(fd, line);
	if (!line)
		return (NULL);
	remainder = process_remainder(line);
	return (line);
}

/* int main()
{
	int i = 1;
	int fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Erro ao abrir o arquivo");
		return 1;
	}
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line[%d]:%s", i, line);
		free(line);
		i++;
	}
	close(fd);
	return 0;
} */
