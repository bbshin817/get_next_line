/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaba <sbaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:41:51 by sbaba             #+#    #+#             */
/*   Updated: 2024/12/02 16:59:08 by sbaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
    char    *str;
    char    *new_str;
    char    *buff;
    ssize_t buff_size;
    size_t  str_size;
    int     i;
    int     f;

    str_size = 0;
    while (1)
    {
        buff = malloc(BUFFER_SIZE);
        if (!buff)
            return (NULL);
        buff_size = read(fd, buff, BUFFER_SIZE);
        if (buff_size == 0)
        {
            // ファイルの終端へ達した場合
            return (str);
        }
        else if (buff_size == -1)
        {
            // ファイルの読み込み自体に失敗した場合
            return (NULL);
        }
        else
        {
            // ファイルの中身がある場合
            new_str = malloc(str_size + BUFFER_SIZE + (sizeof(char)));
            if (!new_str)
                return (NULL);
            // 既存データを新しく確保した配列へコピー
            i = 0;
            while (i < str_size)
            {
                new_str[i] = str[i];
                i++;
            }
            free(str);
            str = new_str;
            // 今回取得したデータも配列へコピー
            i = str_size;
            f = 0;
            while (i < str_size + BUFFER_SIZE)
            {
                str[i] = buff[f];
                i++;
                f++;
            }
            i = str_size;
            while (i < str_size + BUFFER_SIZE)
            {
                // 改行文字を見つけたら
                if(str[i] == '\0')
                    str[str_size + BUFFER_SIZE] = '\0';
                    return (str);
                i++;
            }
        }
    }
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int     fd;
    char    *result;

    fd = open("./textfile.txt", O_RDONLY);
    result = get_next_line(fd);
    printf("[Result]\n-----\n%s-----", result);
}