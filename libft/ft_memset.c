/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:09:21 by agodeanu          #+#    #+#             */
/*   Updated: 2024/08/06 17:55:55 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *sth, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) sth;
	while (n-- > 0)
		*ptr++ = (unsigned char) c;
	return (sth);
}
