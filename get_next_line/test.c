/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:18:41 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/01/21 18:46:57 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static char buff_ax[BUFFER_SIZE + 1u];
    char        *line;
    int         read_var;

    if (BUFFER_SIZE == 0 || fd < 0)
        return (NULL);
    line = NULL;
    while (!line || !ft_strchr(line, '\n'))
    {
        if (!(*buff_ax))
        {
            read_var = read(fd, buff_ax, BUFFER_SIZE);
            if (read_var < 0)
            {
                if (line)
                    free(line);
                return (NULL);
            }
            if (read_var == 0)
                return (line);
            buff_ax[read_var] = '\0';
        }
        line = ft_appender(buff_ax, line);
    }
    return (line);
}