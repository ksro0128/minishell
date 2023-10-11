/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cll_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:29:39 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	cll_print(t_list *node, int size)
{
	int	i;

	i = -1;
	if (node == 0)
		return ;
	ft_printf("CLL [FOR] res: ");
	while (++ i < size)
	{
		ft_printf("%d => ", node->num);
		node = node->next;
	}
	ft_printf("\n");
}
