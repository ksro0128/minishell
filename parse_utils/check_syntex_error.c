/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntex_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:24:37 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/04 15:59:20 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntex_error(t_msh *msh, t_token *token_list, int prev_meta_flag)
{
	char	*last_meta_char;

	while (token_list && is_white_space(token_list->stat))
		token_list = token_list->next;
	if (token_list && token_list->stat == M_PIPE)
		prev_meta_flag = M_PIPE;
	while (token_list)
	{
		if (token_list->stat / 10 == S_META && \
			token_list->stat != M_SPACE && token_list->stat != M_TAB)
		{
			if ((prev_meta_flag / 10 == S_META && prev_meta_flag != M_PIPE) || \
				(prev_meta_flag == M_PIPE && token_list->stat == M_PIPE))
				return (handling_error(msh, E_SYNTAX, token_list->str, NULL));
			prev_meta_flag = token_list->stat;
			last_meta_char = token_list->str;
		}
		else if (token_list->stat == S_UNDEF)
			prev_meta_flag = 0;
		token_list = token_list->next;
	}
	if (prev_meta_flag != 0)
		return (handling_error(msh, E_SYNTAX, last_meta_char, NULL));
	return (SUCCESS);
}
