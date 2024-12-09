/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaba <sbaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:59:02 by sbaba             #+#    #+#             */
/*   Updated: 2024/12/04 18:05:20 by sbaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

char    *get_next_line(int fd)
{
    static char *str;
    char        *buff[BUFFER_SIZE];
    ssize_t     buff_size;
    char        *ret;
    char        *new_ret;
    size_t      ret_size;
    int         i;
    int         f;

    if (!str)
    {
        i = 0;
        while (str[i] != '\0')
            i++;
        new_ret = malloc(i * sizeof(char));
        f = 0;
        while (f < i)
        {
            new_ret[f] = str[f];
            f++;
        }
        ret = new_ret;
        free(new_ret);
    }

    ret_size = 0;
    while(1)
    {
        buff_size = read(fd, buff, BUFFER_SIZE);
        if (buff_size == 0)
        {
            // ファイルの終端へ達した場合
        }
        else if (buff_size == -1)
        {
            // ファイルの読み込みに失敗した場合
        }
        else
        {
            // ファイルの中身が存在する場合
            i = 0;
            while (i < buff_size)
            {
                // 改行文字に遭遇した場合
                if (buff[i] == '\n')
                {
                    str = malloc((buff_size - i) * sizeof(char));
                    if (!str)
                        return (NULL);
                    f = i;
                    i = 0;
                    while (f < buff_size)
                    {
                        str[i] = buff[f];
                        f++;
                        i++;
                    }
                    return (ret);
                }
                else
                {
                    new_ret = malloc(ret_size + 1);
                    if (!new_ret)
                        return (NULL);
                    f = 0;
                    while (f < ret_size)
                    {
                        new_ret[f] = ret[f];
                        f++;
                    }
                    ret = new_ret;
                    free(new_ret);
                    ret[f] = buff[i];
                    ret_size++;
                }
                i++;
            }
        }
    }
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
    printf("[Result]\n-----\n%s\n-----", result);
}