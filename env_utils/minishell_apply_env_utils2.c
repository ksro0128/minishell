/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_apply_env_utils2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:04:06 by surkim            #+#    #+#             */
/*   Updated: 2023/10/04 17:29:36 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	devided_by_ws_first(t_env_tmp *token, char *str, int *i)
{
	if (str[*i] == ' ' || str[*i] == '\t')
	{
		token->str = ft_strdup(" ");
		token->stat = ' ';
		(*i)++;
	}
	else
		token->str = getstr_until_white_space(str, i);
}

void	devided_by_ws_remain(t_env_tmp *token, char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == ' ' || str[*i] == '\t')
		{
			insert_env_tmp(token, ft_strdup(" "), ' ');
			token = token->next;
		}
		else
		{
			insert_env_tmp(token, getstr_until_white_space(str, i), 1);
			(*i)--;
			token = token->next;
		}
		(*i)++;
	}
}

void	devided_by_white_space(t_env_tmp *token)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup(token->str);
	free(token->str);
	devided_by_ws_first(token, str, &i);
	devided_by_ws_remain(token, str, &i);
	free(str);
}

void	apply_env_token(t_env_tmp *token, t_msh *msh)
{
	int		s;
	int		i;
	char	*rt;

	s = 0;
	i = 0;
	rt = ft_strdup("");
	while (token->str[i])
	{
		if (token->str[i] == '$')
		{
			rt = ft_strjoin_12free(rt, cut_s_to_i(token->str, s, i));
			rt = ft_strjoin_12free(rt, extract_env(token->str, &i, msh));
			s = i + 1;
		}
		i++;
	}
	rt = ft_strjoin_12free(rt, cut_s_to_i(token->str, s, i));
	free(token->str);
	token->str = rt;
}

void	free_env_tmp(t_env_tmp *head)
{
	t_env_tmp	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->str != NULL)
			free(tmp->str);
		free(tmp);
	}
}
