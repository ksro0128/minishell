/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc_and_tmp_file.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:56:51 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/04 16:28:55 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes_str(char *str)
{
	t_env_tmp	*head;
	t_env_tmp	*tmp;
	char		*rt;

	head = make_tmp_list_devided_by_quotes(str);
	apply_merge_dollar_quotes(head);
	rt = merge_token_to_str(head);
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->str != NULL)
			free(tmp->str);
		free(tmp);
	}
	return (rt);
}

int	check_limiter(char *limiter)
{
	int	i;

	i = 0;
	while (limiter[i])
	{
		if (limiter[i] == '\'' || limiter[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

int	set_heredoc_and_tmp_file2(t_token *cur, t_msh *msh, char *tmp_file)
{
	tmp_file = make_heredoc(cur->str, msh);
	if (tmp_file == NULL)
		return (ERROR);
	set_token(cur, F_HEREDOC, tmp_file);
	return (SUCCESS);
}

int	set_heredoc_and_tmp_file(t_token *token_list, t_msh *msh)
{
	t_token	*cur;
	char	*tmp_file;

	cur = token_list;
	while (cur)
	{
		if (cur->stat == M_R_DSHIFT)
		{
			set_token(cur, M_R_SSHIFT, ft_strdup("<"));
			cur = cur->next;
			while (cur && (cur->stat == M_SPACE || cur->stat == M_TAB))
				cur = cur->next;
			if (cur && cur->stat == S_UNDEF)
			{
				if (set_heredoc_and_tmp_file2(cur, msh, tmp_file) == ERROR)
					return (ERROR);
			}
			else
				continue ;
		}
		if (cur)
			cur = cur->next;
	}
	return (SUCCESS);
}
