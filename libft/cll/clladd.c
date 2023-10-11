/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clladd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:30:02 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	clladd(t_list	**head, int num)
{
	t_list	*new_node;
	t_list	*node;

	node = *head;
	new_node = cll_new(num);
	if (new_node == 0)
		return (0);
	if (node == 0)
		node = new_node;
	new_node->next = node;
	new_node->prev = node->prev;
	node->prev->next = new_node;
	node->prev = new_node;
	*head = new_node;
	return (1);
}
