/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_apply_env_utils3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:06:59 by surkim            #+#    #+#             */
/*   Updated: 2023/10/04 17:29:32 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	apply_env_tmp_to_token(t_token *token, t_env_tmp *head)
{
	int	stat;

	stat = token->stat;
	head = head->next;
	free(token->str);
	token->str = ft_strdup(head->str);
	head = head->next;
	if (token->stat == F_CMD)
		stat = F_WORD;
	while (head)
	{
		insert_token(token, ft_strdup(head->str), stat);
		token = token->next;
		head = head->next;
	}
	return (1);
}

void	insert_env_tmp(t_env_tmp *cur, char *str, int stat)
{
	t_env_tmp	*new_token;

	new_token = create_env_tmp(str, stat);
	if (cur->next == NULL)
		cur->next = new_token;
	else
	{
		new_token->next = cur->next;
		cur->next = new_token;
	}
}

void	remove_ws_env_tmp(t_env_tmp *head)
{
	t_env_tmp	*tmp;

	while (head->next)
	{
		if (head->next->stat == ' ')
		{
			tmp = head->next;
			head->next = head->next->next;
			free(tmp->str);
			free(tmp);
		}
		else
			head = head->next;
	}
}

void	apply_merge_env_tmp(t_env_tmp *head)
{
	t_env_tmp	*tmp;

	head = head->next;
	while (head->next)
	{
		if (head->stat != ' ' && head->next->stat != ' ')
		{
			head->str = ft_strjoin_12free(head->str, head->next->str);
			tmp = head->next;
			head->next = head->next->next;
			free(tmp);
		}
		else
			head = head->next;
	}
}

void	insert_token(t_token *cur, char *str, int stat)
{
	t_token	*new_token;

	new_token = create_token(str, stat);
	if (cur->next == NULL)
		cur->next = new_token;
	else
	{
		new_token->next = cur->next;
		cur->next = new_token;
	}
}
