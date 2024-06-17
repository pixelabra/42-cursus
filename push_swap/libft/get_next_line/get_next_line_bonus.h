/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:24:04 by agodeanu          #+#    #+#             */
/*   Updated: 2024/06/17 16:24:04 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512

# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

char	*get_next_line(int fd);
size_t	gnl_strlen(const char *str, int nbr);
char	*gnl_strchr(const char *str, int c);
char	*gnl_strjoin(char const *s1, char const *s2);
void	*gnl_memmove(void *dest, const void *src, size_t n);
char	*gnl_appender(char *buff_ax, char *line);

#endif
