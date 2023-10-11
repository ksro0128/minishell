/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cllpop_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:49:55 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*cllpop_next(t_list **head)
{
	t_list	*node;
	t_list	*next_node;

	node = *head;
	if (node == 0)
		return (0);
	next_node = node->next;
	if (next_node == node)
		node = 0;
	else
	{
		node->next = node->next->next;
		node->next->prev = node;
	}
	next_node->next = next_node;
	next_node->prev = next_node;
	return (next_node);
}
