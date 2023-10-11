/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_by_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:39:50 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/04 12:10:04 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_valid_quotes(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			i ++;
			while (cmd[i] && cmd[i] != '\'')
				i ++;
			if (cmd[i] == '\0')
				return (ERROR);
		}
		else if (cmd[i] == '\"')
		{
			i ++;
			while (cmd[i] && cmd[i] != '\"')
				i ++;
			if (cmd[i] == '\0')
				return (ERROR);
		}
		i ++;
	}
	return (SUCCESS);
}

void	separate_by_quotes(t_token **token_list, char *cmd)
{
	int		i;
	int		prev_i;
	t_token	*head;

	i = 0;
	prev_i = 0;
	head = create_token(NULL, S_UNDEF);
	*token_list = head;
	while (cmd[i])
	{
		if (cmd[i] == C_SINGLE_QUOTE || cmd[i] == C_DOUBLE_QUOTE)
		{
			add_token(head, cmd + prev_i, i - prev_i, S_UNDEF);
			prev_i = i;
			i ++;
			while (cmd[i] && cmd[i] != cmd[prev_i])
				i ++;
			if (cmd[i] == cmd[prev_i])
				add_token(head, cmd + prev_i, i - prev_i + 1, S_QUOTE);
			prev_i = i + 1;
		}
		i ++;
	}
	add_token(head, cmd + prev_i, i - prev_i, S_UNDEF);
}
