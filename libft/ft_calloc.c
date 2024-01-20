/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:02:43 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/15 23:02:45 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*ptr;

	if (elsize && nelem > SIZE_MAX / elsize)
		return (NULL);
	ptr = malloc(elsize * nelem);
	if (!ptr)
		return (NULL);
	return (ft_memset(ptr, 0, nelem * elsize));
}
