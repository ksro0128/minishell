/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cll_delone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:09:23 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:41:02 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	cll_delone(t_list **head)
{
	t_list	*node;

	node = (*head);
	if (node == 0)
		return ;
	if (node->prev == node)
		(*head) = 0;
	else
	{
		(*head) = node->next;
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	free(node);
}
