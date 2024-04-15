/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:06:38 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/15 23:06:39 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*temp_next;

	if (!lst || !del)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		temp_next = temp->next;
		ft_lstdelone(temp, del);
		temp = temp_next;
	}
	*lst = NULL;
}
