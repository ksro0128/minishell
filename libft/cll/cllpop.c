/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cllpop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:17:36 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*cllpop(t_list **head)
{
	t_list	*node;

	node = (*head);
	if (node == 0)
		return (0);
	if (node->prev == node)
		(*head) = 0;
	else
	{
		(*head) = node->next;
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	node->next = node;
	node->prev = node;
	return (node);
}
