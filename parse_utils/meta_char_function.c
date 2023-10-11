/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_char_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:32:19 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/25 09:35:34 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_status(char c, t_token *tmp, char *str)
{
	if (c == C_SPACE)
		set_token(tmp, M_SPACE, str);
	else if (c == C_TAB)
		set_token(tmp, M_TAB, str);
	else if (c == C_PIPE)
		set_token(tmp, M_PIPE, str);
	else if (c == C_R_SHIFT)
	{
		if (tmp->stat == M_R_DSHIFT)
			set_token(tmp, M_R_DSHIFT, ft_strdup("<<"));
		else
			set_token(tmp, M_R_SSHIFT, str);
	}
	else if (c == C_L_SHIFT)
	{
		if (tmp->stat == M_L_DSHIFT)
			set_token(tmp, M_L_DSHIFT, ft_strdup(">>"));
		else
			set_token(tmp, M_L_SSHIFT, str);
	}
	else
		set_token(tmp, S_UNDEF, str);
}

void	set_meta_char(t_token *head, char *str, int idx)
{
	t_token	*tmp;
	char	c;

	tmp = head;
	c = str[0];
	while (tmp->next)
		tmp = tmp->next;
	if (c == C_R_SHIFT && tmp->stat == M_R_SSHIFT)
		set_token(tmp, M_R_DSHIFT, ft_strdup("<<"));
	else if (c == C_L_SHIFT && tmp->stat == M_L_SSHIFT)
		set_token(tmp, M_L_DSHIFT, ft_strdup(">>"));
	else
	{
		add_token(head, str, idx, S_META_CHAR);
		if (tmp->next)
			tmp = tmp->next;
		set_status(c, tmp, ft_strdup(tmp->str));
	}
}
