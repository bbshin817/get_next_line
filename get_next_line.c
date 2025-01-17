/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:41:51 by sbaba             #+#    #+#             */
/*   Updated: 2025/01/17 21:18:25 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*do_read(int fd, char *cache)
{
	char	*tmp;
	ssize_t	bytesize;

	tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	bytesize = 1;
	while (!ft_strchr(cache, '\n') && 0 != bytesize)
	{
		bytesize = read(fd, tmp, BUFFER_SIZE);
		if (-1 == bytesize)
		{
			free(tmp);
			return (NULL);
		}
		tmp[bytesize] = '\0';
		cache = ft_strjoin(cache, tmp);
	}
	free(tmp);
	return (cache);
}

char	*search_line(char *cache)
{
	int		i;
	char	*line;

	i = 0;
	if (!cache[i])
		return (NULL);
	while (cache[i] && cache[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (cache[i] && cache[i] != '\n')
	{
		line[i] = cache[i];
		i++;
	}
	if (cache[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_after_line_breaks(char *cache)
{
	int		i;
	int		r;
	char	*rest;

	i = 0;
	while (cache[i] && cache[i] != '\n')
		i++;
	if (!cache[i])
	{
		free(cache);
		return (NULL);
	}
	rest = (char *)malloc((ft_strlen(cache) - i + 1) * sizeof(char));
	if (!rest)
		return (NULL);
	i++;
	r = 0;
	while (cache[i])
		rest[r++] = cache[i++];
	rest[r] = '\0';
	free(cache);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	cache = do_read(fd, cache);
	if (!cache)
		return (NULL);
	line = search_line(cache);
	cache = get_after_line_breaks(cache);
	return (line);
}
