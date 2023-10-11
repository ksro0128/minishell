/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clladd_prev.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:15:01 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	clladd_prev(t_list **head, int num)
{
	t_list	*new_node;

	new_node = cll_new(num);
	if (new_node == 0)
		return (0);
	if ((*head) == 0)
		(*head) = new_node;
	else
	{
		new_node->next = (*head);
		new_node->prev = (*head)->prev;
		(*head)->prev->next = new_node;
		(*head)->prev = new_node;
	}
	return (1);
}
