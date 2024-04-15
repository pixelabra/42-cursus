/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:02:34 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/15 23:02:35 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *sth, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) sth;
	while (n-- > 0)
		*ptr++ = 0;
	return ;
}
