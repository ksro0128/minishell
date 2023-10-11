/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cllpush_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:48:07 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	cllpush_next(t_list **head, t_list *new_node)
{
	t_list	*node;

	node = *head;
	if (new_node == 0)
		return (0);
	if (node == 0)
		node = new_node;
	if (node == 0)
		node = new_node;
	new_node->next = node->next;
	new_node->prev = node;
	node->next = new_node;
	if (node->prev == node)
		node->prev = new_node;
	return (1);
}
