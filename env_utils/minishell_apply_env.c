/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_apply_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:25:08 by surkim            #+#    #+#             */
/*   Updated: 2023/10/04 17:29:25 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_env(char *str, int *i, t_msh *msh)
{
	(*i)++;
	if (str[*i] == '?')
		return (ft_itoa(msh->exit_code));
	else if (str[*i] == '"')
		return (extract_env_dq(str, i));
	else if (ft_isalpha(str[*i]) || str[*i] == '_')
		return (extract_env_var(str, i, msh->env_list));
	else
	{
		(*i)--;
		return (ft_strdup("$"));
	}
}

t_env_tmp	*create_normal_token(char *str, int *i)
{
	int			s;
	t_env_tmp	*rt;

	s = *i;
	(*i)++;
	while (str[*i] && str[*i] != '"' && str[*i] != '\'')
		(*i)++;
	rt = create_env_tmp(cut_s_to_i(str, s, *i), 1);
	(*i)--;
	return (rt);
}

t_env_tmp	*make_tmp_list_devided_by_quotes(char *str)
{
	t_env_tmp	*head;
	t_env_tmp	*rt;
	int			s;
	int			i;

	rt = create_env_tmp(NULL, 0);
	head = rt;
	i = 0;
	s = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			head->next = create_quotes_token(str, &i);
			head = head->next;
		}
		else
		{
			head->next = create_normal_token(str, &i);
			head = head->next;
		}
		i++;
	}
	return (rt);
}

char	*getstr_until_white_space(char *str, int *i)
{
	int		s;
	char	*rt;

	s = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t')
		(*i)++;
	rt = cut_s_to_i(str, s, *i);
	return (rt);
}

int	apply_env_to_one_token(t_token *token, t_msh *msh)
{	
	t_env_tmp	*head;

	head = make_tmp_list_devided_by_quotes(token->str);
	apply_merge_dollar_quotes(head);
	apply_env_tmp(head, msh);
	apply_devide_by_white_space(head);
	apply_merge_env_tmp(head);
	remove_ws_env_tmp(head);
	if (head->next == NULL)
		insert_env_tmp(head, ft_strdup(""), 1);
	if (token->stat == F_FILE && head->next->next != NULL)
		token->stat = F_AMBERR;
	else
		apply_env_tmp_to_token(token, head);
	free_env_tmp(head);
	return (SUCCESS);
}
