/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cllswap_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:09:01 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	cllswap_next(t_list *node)
{
	t_list	*next_node;
	int		tmp_num;

	if (node == 0)
		return ;
	if (node->next == node)
		return ;
	next_node = node->next;
	tmp_num = node->num;
	node->num = next_node->num;
	next_node->num = tmp_num;
}
