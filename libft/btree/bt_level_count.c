/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_level_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:15:33 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	bt_level_recur(t_btree *root, int level)
{
	int	left_lvl;
	int	right_lvl;

	if (root == 0)
		return (level);
	left_lvl = bt_level_recur(root->left, level + 1);
	right_lvl = bt_level_recur(root->right, level + 1);
	if (left_lvl > right_lvl)
		return (left_lvl);
	else
		return (right_lvl);
}

int	bt_level_count(t_btree *root)
{
	int	lvl;
	int	res;

	lvl = 0;
	res = bt_level_recur(root, lvl);
	return (res);
}
