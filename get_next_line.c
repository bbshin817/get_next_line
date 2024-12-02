/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaba <sbaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:41:51 by sbaba             #+#    #+#             */
/*   Updated: 2024/12/02 15:49:53 by sbaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
    char    *str;
    ssize_t result;

    result = read(fd, str, BUFFER_SIZE);
    if (result == 0)
    {
        // ファイルの終端へ達した場合
    }
    else if (result == -1)
    {
        // ファイルの読み込み自体に失敗した場合
        return (NULL);
    }
    else
    {
        // ファイルの中身がある場合
    }
}