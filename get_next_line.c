/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaba <sbaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:41:51 by sbaba             #+#    #+#             */
/*   Updated: 2024/12/09 16:54:25 by sbaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

static int	do_read(int fd, char *buff, ssize_t *buff_len, ssize_t *buff_pos)
{
	*buff_len = read(fd, buff, BUFFER_SIZE);
	*buff_pos = 0;
	if (*buff_len <= 0)
	{
		free(buff);
		return (0);
	}
	return (1);
}

static char	*get_line(char str, char *line, size_t *line_size)
{
	char	*new_line;
	size_t	i;

	new_line = malloc(*line_size + (*line_size == 0) + 1);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	if (line != NULL)
	{
		printf("Line: %s\n", line);
		i = 0;
		while (i < *line_size)
		{
			new_line[i] = line[i];
			i++;
		}
		free(line);
	}
	line = new_line;
	line[(*line_size)++] = str;
	// printf("Line: \"%s\", ", line);
	if (str == '\n')
	{
		line[*line_size] = '\0';
		return (1);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*buff;
	static ssize_t	buff_len;
	static ssize_t	buff_pos;
	char			*line;
	size_t			line_size;

	line = NULL;
	line_size = 0;

	if (buff == 0)
	{
		buff = malloc(BUFFER_SIZE);
		if (!buff || do_read(fd, buff, &buff_len, &buff_pos) == 0)
			return (NULL);
	}
	while (1)
	{
		while (buff_pos < buff_len)
		{
			if (!get_line(buff[buff_pos++], &line, &line_size))
				return (line);
		}
		if (do_read(fd, buff, &buff_len, &buff_pos) == 0)
			return (line);
	}
	return (buff);
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int     fd;
    char    *result;

    fd = open("./textfile.txt", O_RDONLY);
    result = get_next_line(fd);
    printf("[Result]\n-----\n\"%s\"\n-----", result);
}