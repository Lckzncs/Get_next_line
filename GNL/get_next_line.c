/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludo-nas <ludo-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:14:36 by ludo-nas          #+#    #+#             */
/*   Updated: 2024/11/14 18:50:56 by ludo-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append_buffer_to_line(char **line, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(*line, buffer);
	free(*line);
	return (temp);
}

static char	*handle_remainder(char **line, char **remainder)
{
	char	*newline_pos;
	char	*temp;

	newline_pos = ft_strchr(*remainder, '\n');
	if (newline_pos)
	{
		*newline_pos = '\0';
		temp = ft_strjoin(*line, *remainder);
		free(*line);
		*line = temp;
		temp = ft_strdup(newline_pos + 1);
		free(*remainder);
		*remainder = temp;
		return (*line);
	}
	else
	{
		temp = ft_strjoin(*line, *remainder);
		free(*line);
		*line = temp;
		free(*remainder);
		*remainder = NULL;
	}
	return (NULL);
}

static char	*read_buffer(int fd, char **line, char *buffer, char **remainder)
{
	ssize_t	bytes_read;
	char	*newline_pos;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		newline_pos = ft_strchr(buffer, '\n');
		if (newline_pos)
		{
			*newline_pos = '\0';
			*line = append_buffer_to_line(line, buffer);
			*remainder = ft_strdup(newline_pos + 1);
			return (*line);
		}
		*line = append_buffer_to_line(line, buffer);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (**line != '\0')
		return (*line);
	free(*line);
	*line = NULL;
	return (*line);
}

static char	*process_buffer(int fd, char **line, char *buffer, char **remainder)
{
	char	*result;

	if (*remainder)
	{
		result = handle_remainder(line, remainder);
		if (result)
			return (result);
	}
	return (read_buffer(fd, line, buffer, remainder));
}

char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(line);
		return (NULL);
	}
	line = process_buffer(fd, &line, buffer, &remainder);
	free(buffer);
	return (line);
}

#include <stdio.h>

int main()
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
		printf("line[%d]: %s\n", i, line);
		free(line);
		i++;
	}
	close(fd);
	return 0;
}