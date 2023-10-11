/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_insert_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:28:31 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	bt_insert_data(t_btree **root, void *item, int (*cmpf)(void*, void*))
{
	t_btree	*tmp;
	t_btree	*new_node;

	tmp = *root;
	new_node = bt_create_node(item);
	if (*root == 0)
		tmp = new_node;
	if (new_node == 0 || *root == 0)
		return ;
	while (tmp)
	{
		if (cmpf(tmp->item, item))
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}
	tmp = new_node;
}
