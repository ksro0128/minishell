/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main_apply_env.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:53:20 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/04 16:56:41 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_redir(t_msh *msh, t_exec_mat *mat)
{
	t_token	*cmd;

	cmd = mat->token_list;
	while (cmd)
	{
		if (cmd->stat == F_REDIR_IN)
		{
			mat->fd_in = open(cmd->next->str, O_RDONLY);
			if (mat->fd_in < 0)
				return (handling_error(msh, E_OPEN, cmd->next->str, NULL));
		}
		if (cmd->stat == F_REDIR_OUT)
		{
			mat->fd_out = open(cmd->next->str, O_WRONLY | O_CREAT);
			if (mat->fd_out < 0)
				return (handling_error(msh, E_OPEN, cmd->next->str, NULL));
		}
		cmd = cmd->next;
	}
	return (1);
}

char	**make_argument(t_token *token_list)
{
	int		len;
	t_token	*cur;
	char	**arg;

	len = 0;
	cur = token_list;
	while (cur && cur->stat != F_PIPE)
	{
		if (cur->stat == F_CMD || cur->stat == F_WORD)
			len ++;
		cur = cur->next;
	}
	arg = (char **) malloc(sizeof(char *) * (len + 1));
	if (arg == NULL)
		exit(1);
	cur = token_list;
	len = 0;
	while (cur && cur->stat != F_PIPE)
	{
		if (cur->stat == F_CMD || cur->stat == F_WORD)
			arg[len ++] = ft_strdup(cur->str);
		cur = cur->next;
	}
	arg[len] = NULL;
	return (arg);
}

int	find_cmd_and_arg(t_exec_mat *mat)
{
	t_token	*token_list;
	char	**path;

	token_list = mat->token_list;
	path = mat->msh->path;
	mat->arg = make_argument(token_list);
	mat->cmd = NULL;
	while (token_list)
	{
		if (token_list->stat == F_CMD)
		{
			mat->cmd = ft_strdup(token_list->str);
			return (SUCCESS);
		}
		token_list = token_list->next;
	}
	return (ERROR);
}

void	applying_env(t_msh *msh, t_exec_mat *cur_mat)
{
	t_token	*cur_token;
	t_token	*next_token;

	cur_token = cur_mat->token_list;
	while (cur_token)
	{
		next_token = cur_token->next;
		if (apply_env_to_one_token(cur_token, msh) == ERROR)
			return ;
		cur_token = next_token;
	}
	find_cmd_and_arg(cur_mat);
}
