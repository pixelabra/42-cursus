/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:06:00 by agodeanu          #+#    #+#             */
/*   Updated: 2024/08/06 17:04:15 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int nbr)
{
	int	nbr_count;

	nbr_count = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		nbr_count++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		nbr_count++;
	}
	return (nbr_count + 1);
}

static char	*ft_itostr(char *nbr_str, int nbr, int nbr_count)
{
	nbr_str[nbr_count--] = '\0';
	if (nbr < 0)
	{
		nbr_str[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		nbr_str[nbr_count--] = (char)(nbr % 10) + '0';
		nbr /= 10;
	}
	return (nbr_str);
}

char	*ft_itoa(int nbr)
{
	char	*nbr_str;
	int		nbr_count;

	if (nbr == 0)
		return (ft_strdup("0"));
	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	nbr_count = ft_count(nbr);
	nbr_str = malloc(sizeof(char) * (nbr_count + 1));
	if (!nbr_str)
		return (NULL);
	return (ft_itostr(nbr_str, nbr, nbr_count));
}
