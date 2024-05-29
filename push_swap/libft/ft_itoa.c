/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:06:00 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/16 01:39:50 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int	nbr_count;

	nbr_count = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n *= -1;
		nbr_count++;
	}
	while (n / 10 > 0)
	{
		n /= 10;
		nbr_count++;
	}
	return (nbr_count + 1);
}

static char	*ft_itostr(int n, char *nbr_str, int nbr_count)
{
	int	number;

	number = n;
	nbr_str[nbr_count] = '\0';
	while (nbr_count)
	{
		if (number < 0)
			number *= -1;
		if (n < 0 && number == 0)
		{
			nbr_str[0] = 45;
			break ;
		}
		nbr_str[nbr_count - 1] = (char)((number % 10) + 48);
		number /= 10;
		nbr_count--;
	}
	return (nbr_str);
}

char	*ft_itoa(int n)
{
	char	*nbr_str;
	int		nbr_count;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nbr_count = ft_count(n);
	nbr_str = (char *) malloc(sizeof(char) * (size_t)(nbr_count + 1));
	if (!nbr_str)
		return (NULL);
	return (ft_itostr(n, nbr_str, nbr_count));
}
