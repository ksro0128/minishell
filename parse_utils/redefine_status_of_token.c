/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redefine_status_of_token.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:29:09 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/25 09:52:52 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redefine_status_of_token(t_token *token_list)
{
	int	cmd;
	int	prev_stat;

	cmd = 0;
	prev_stat = -2;
	while (token_list)
	{
		if (token_list->stat == S_UNDEF)
		{
			if (prev_stat >= M_R_SSHIFT && prev_stat <= M_L_DSHIFT)
				token_list->stat = F_FILE;
			else if (cmd == 0)
			{
				token_list->stat = F_CMD;
				cmd = 1;
			}
			else
				token_list->stat = F_WORD;
		}
		if (token_list->stat == M_PIPE)
			cmd = 0;
		prev_stat = token_list->stat;
		token_list = token_list->next;
	}
}
