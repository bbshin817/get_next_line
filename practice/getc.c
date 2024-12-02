/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaba <sbaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:04:44 by sbaba             #+#    #+#             */
/*   Updated: 2024/11/20 19:20:51 by sbaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int getchar(int fd)
{
    static char buf[BUFFER_SIZE];
    static char *bufp;
    static int  n;

    n = 0;
    if (0 == n)
    {
        n = read(0, buf, BUFFER_SIZE);
        bufp = buf;
    }
    if (0 <= n--)
        return (unsigned char) *bufp++;
    else
        return (EOF);
}