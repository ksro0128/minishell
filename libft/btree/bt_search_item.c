/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_search_item.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:48:54 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*bt_search_item(t_btree *root, void *data_ref, \
						int (*cmpf)(void *, void *))
{
	void	*left_item;
	void	*right_item;

	if (root == 0)
		return (0);
	if (cmpf(root->item, data_ref))
		return (root->item);
	left_item = bt_search_item(root->left, data_ref, cmpf);
	if (left_item != 0)
		return (left_item);
	right_item = bt_search_item(root->right, data_ref, cmpf);
	if (right_item != 0)
		return (right_item);
	return (0);
}
