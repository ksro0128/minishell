/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_apply_env_utils4.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:10:28 by surkim            #+#    #+#             */
/*   Updated: 2023/10/04 17:29:29 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	apply_env_tmp(t_env_tmp *head, t_msh *msh)
{
	while (head)
	{
		if (head->str != NULL && head->stat != '\'')
			apply_env_token(head, msh);
		head = head->next;
	}
}

void	apply_devide_by_white_space(t_env_tmp *head)
{
	t_env_tmp	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->str != NULL && tmp->stat == 1)
			devided_by_white_space(tmp);
	}
}

void	apply_merge_dollar_quotes(t_env_tmp *head)
{
	int		i;
	char	*tmp;

	head = head->next;
	while (head->next)
	{
		if (head->next->stat == '\'' || head->next->stat == '"')
		{
			i = 0;
			while (head->str[i])
				i++;
			if (head->str[i - 1] == '$')
			{
				tmp = cut_s_to_i(head->str, 0, i - 1);
				free(head->str);
				head->str = tmp;
			}
		}
		head = head->next;
	}
}

char	*extract_env_var(char *str, int *i, t_env *env_list)
{
	int		s;
	char	*key;
	char	*rt;

	s = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	key = cut_s_to_i(str, s, *i);
	env_list = env_list->next;
	while (env_list)
	{
		if (ft_strncmp(key, env_list->key, ft_strlen(key) + 1) == 0)
		{
			rt = ft_strdup(env_list->value);
			break ;
		}
		env_list = env_list->next;
	}
	if (env_list == NULL)
		rt = ft_strdup("");
	free(key);
	(*i)--;
	return (rt);
}
