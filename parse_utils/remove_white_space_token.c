/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_white_space_token.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:00:55 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/04 16:04:50 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_token(t_token *token)
{
	free(token->str);
	free(token);
}

void	remove_front(t_token **token_list)
{
	t_token	*tmp;

	tmp = *token_list;
	if (tmp->stat == M_SPACE || tmp->stat == M_TAB)
	{
		*token_list = (*token_list)->next;
		remove_token(tmp);
	}
}

void	remove_back(t_token *token_list)
{
	t_token	*tmp;
	t_token	*next;

	while (token_list)
	{
		if (token_list->next && \
		(token_list->next->stat == M_SPACE || token_list->next->stat == M_TAB))
		{
			next = token_list->next;
			while (next && (next->stat == M_SPACE || next->stat == M_TAB))
			{
				tmp = next;
				next = next->next;
				remove_token(tmp);
			}
			token_list->next = next;
		}
		token_list = token_list->next;
	}
}

void	remove_white_space_token(t_token **token_list)
{
	remove_back(*token_list);
	remove_front(token_list);
}
