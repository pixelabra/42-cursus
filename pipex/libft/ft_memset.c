/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:09:21 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/15 23:09:22 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *sth, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) sth;
	while ((int) n-- > 0)
		*ptr++ = (unsigned char) c;
	return (sth);
}
