/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:12:27 by ppolinta          #+#    #+#             */
/*   Updated: 2024/07/28 16:12:48 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	if (!n)
		while (s1[i] == s2[i] && s1[i] && s2[i])
			i++;
	else
		while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
			i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
