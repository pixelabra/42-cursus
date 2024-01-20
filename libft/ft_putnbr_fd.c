/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:10:47 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/15 23:10:49 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	c = 48;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", sizeof(char) * 11);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", sizeof(char));
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		n %= 10;
	}
	if (n <= 9)
	{
		c = (char)(n + 48);
		write(fd, &c, sizeof(char));
	}
}
