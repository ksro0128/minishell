/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_apply_env_utils1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:00:11 by surkim            #+#    #+#             */
/*   Updated: 2023/10/04 17:29:39 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pass_until_char(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] != c)
		(*i)++;
}

char	*cut_s_to_i(char *str, int s, int i)
{
	char	*rt;
	int		idx;

	rt = (char *)malloc(sizeof (char) * (i - s + 1));
	if (!rt)
		exit(1);
	idx = 0;
	while (s + idx < i)
	{
		rt[idx] = str[s + idx];
		idx++;
	}
	rt[idx] = '\0';
	return (rt);
}

char	*extract_env_dq(char *str, int *i)
{
	char	*rt;
	int		s;

	(*i)++;
	s = *i;
	while (str[*i] != '"')
		(*i)++;
	rt = cut_s_to_i(str, s, *i);
	return (rt);
}

t_env_tmp	*create_env_tmp(char *str, int stat)
{
	t_env_tmp	*rt;

	rt = (t_env_tmp *)malloc(sizeof (t_env_tmp));
	if (!rt)
		exit(1);
	rt->next = NULL;
	rt->str = str;
	rt->stat = stat;
	return (rt);
}

t_env_tmp	*create_quotes_token(char *str, int *i)
{
	int			s;
	t_env_tmp	*rt;

	s = *i;
	(*i)++;
	while (str[*i] != str[s])
		(*i)++;
	rt = create_env_tmp(cut_s_to_i(str, s + 1, *i), str[s]);
	return (rt);
}
