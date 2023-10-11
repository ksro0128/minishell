/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_except_meta_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:51:00 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/25 16:00:53 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*merge_two_quote_token(t_token *token_list, char *p_str, t_token *prev)
{
	t_token	*cur;
	char	*str;

	cur = prev->next;
	if ((prev->stat == S_QUOTE && cur->stat != S_META_CHAR) || \
		(prev->stat != S_META_CHAR && cur->stat == S_QUOTE) || \
		(prev->stat == S_QUOTE && cur->stat == S_QUOTE))
		str = ft_strjoin_1free(p_str, cur->str);
	else
	{
		if (prev->stat == S_META_CHAR)
			set_meta_char(token_list, p_str, ft_strlen(p_str));
		else
			add_token(token_list, p_str, ft_strlen(p_str), S_UNDEF);
		free(p_str);
		str = ft_strdup(cur->str);
	}
	return (str);
}

void	merge_except_meta_char(t_token **p_token_list)
{
	char	*str;
	t_token	*prev;
	t_token	*token_list;

	prev = *p_token_list;
	if (prev && prev->next == NULL)
		set_status(prev->str[0], prev, ft_strdup(prev->str));
	if (prev == NULL || prev->next == NULL)
		return ;
	str = ft_strdup(prev->str);
	token_list = create_token(NULL, S_UNDEF);
	while (prev->next)
	{
		str = merge_two_quote_token(token_list, str, prev);
		if (str == NULL)
			exit(1);
		prev = prev->next;
	}
	if (is_meta_char(str[0], C_META_CHAR) == TRUE)
		set_meta_char(token_list, str, ft_strlen(str));
	else
		add_token(token_list, str, ft_strlen(str), S_UNDEF);
	free(str);
	delete_all_token(p_token_list);
	*p_token_list = token_list;
}
