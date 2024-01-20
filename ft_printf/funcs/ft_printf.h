/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:32:02 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/25 23:17:30 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

int		ft_putchar(int c);
size_t	ft_strlen(const char *str);
int		ft_putstr(const char *str);
int		ft_putnbr_base(unsigned long number, int base, int check);
int		ft_putnbr(long number);
int		ft_putmem(void *mem);
int		ft_printf(const char *str, ...);

#endif