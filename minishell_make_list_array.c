/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_make_list_array.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:36:58 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/04 16:49:51 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_count(t_token *head)
{
	int	rt;

	rt = 0;
	while (head)
	{
		if (head->stat == M_PIPE)
			rt++;
		head = head->next;
	}
	return (rt);
}

void	set_exec_mat(t_msh *msh, t_exec_mat *ex_mat, t_token *head)
{
	ex_mat->token_list = head;
	ex_mat->fd_in = 0;
	ex_mat->fd_out = 1;
	ex_mat->msh = msh;
	ex_mat->cmd = NULL;
	ex_mat->arg = NULL;
}

void	divide_list(t_msh *msh, t_token *token_list)
{
	int		i;
	t_token	*before;
	t_token	*head;

	i = 0;
	head = token_list;
	while (token_list)
	{
		if (token_list->stat == M_PIPE)
		{
			set_exec_mat(msh, &msh->ex_mat[i], head);
			head = token_list->next;
			before->next = NULL;
			free(token_list->str);
			free(token_list);
			token_list = head;
			i++;
		}
		before = token_list;
		token_list = token_list->next;
	}
	set_exec_mat(msh, &msh->ex_mat[i], head);
}

void	make_list_array(t_msh *msh)
{
	int	pipe_num;

	msh->pipe_cnt = pipe_count(msh->token_list);
	pipe_num = msh->pipe_cnt + 1;
	msh->ex_mat = (t_exec_mat *)malloc(sizeof (t_exec_mat) * pipe_num);
	if (msh->ex_mat == NULL)
		exit(1);
	divide_list(msh, msh->token_list);
}
