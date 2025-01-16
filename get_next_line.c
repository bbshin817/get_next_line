/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:41:51 by sbaba             #+#    #+#             */
/*   Updated: 2024/12/15 22:11:43 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

char    *get_next_line(int fd)
{
	
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