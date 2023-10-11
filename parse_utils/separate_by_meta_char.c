/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_by_meta_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:10:56 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/25 17:40:45 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_meta_char_to_token(t_token *token_list, t_token *cur, char *sepstr)
{
	int	i;
	int	prev_i;

	i = 0;
	prev_i = 0;
	while (i < cur->str_len)
	{
		if (is_meta_char(cur->str[i], sepstr) == TRUE)
		{
			if (prev_i == i)
			{
				add_token(token_list, cur->str + prev_i, 1, S_META_CHAR);
				i ++;
			}
			else
				add_token(token_list, cur->str + prev_i, i - prev_i, S_UNDEF);
			prev_i = i;
		}
		else
			i ++;
	}
	add_token(token_list, cur->str + prev_i, i - prev_i, S_UNDEF);
}

void	separate_by_meta_char(t_token **p_token_list, char *sepstr)
{
	t_token	*cur;
	t_token	*token_list;

	if (*p_token_list == NULL)
		return ;
	cur = *p_token_list;
	token_list = create_token(NULL, S_UNDEF);
	while (cur)
	{
		if (cur->stat != S_QUOTE)
			add_meta_char_to_token(token_list, cur, sepstr);
		else
			add_token(token_list, cur->str, ft_strlen(cur->str), S_QUOTE);
		cur = cur->next;
	}
	delete_all_token(p_token_list);
	*p_token_list = token_list;
}
