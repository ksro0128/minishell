/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_apply_infix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:21:24 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// go root middle
void	bt_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (root == 0)
		return ;
	bt_apply_prefix(root->left, applyf);
	applyf(root->item);
	bt_apply_prefix(root->right, applyf);
}
