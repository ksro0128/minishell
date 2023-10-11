/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:56:55 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/11 10:55:41 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_modi_parent_fd(t_msh *msh)
{
	close(msh->pipe_fd[FD_WR]);
	if (msh->tmp_fd == -2)
		msh->tmp_fd = dup(msh->pipe_fd[FD_RD]);
	else
		dup2(msh->pipe_fd[FD_RD], msh->tmp_fd);
	close(msh->pipe_fd[FD_RD]);
}

void	set_t_msh_before_exec_cmd(t_msh *msh)
{
	msh->tmp_fd = -2;
	msh->path = parsing_path_env(msh);
}

void	execute_cmd_by_pipe2(t_msh *msh, t_exec_mat *cur_mat, int i)
{
	signal_ignore_parent(SIG_CMD);
	cur_mat->pid = fork();
	if (cur_mat->pid > 0)
		ft_modi_parent_fd(msh);
	else if (cur_mat->pid == 0)
	{
		signal_setting_child(SIG_CMD);
		exit(ft_modi_child_fd(msh, cur_mat, i));
	}
	else
	{
		printf("fork error\n");
		exit(1);
	}	
}

void	execute_cmd_by_pipe(t_msh *msh, int i)
{
	int			in;
	int			out;
	t_exec_mat	*cur_mat;

	cur_mat = &msh->ex_mat[i];
	if (pipe(msh->pipe_fd) == FD_ERROR)
	{
		printf("pipe fd error\n");
		exit(1);
	}
	if (msh->pipe_cnt == 0 && is_cmd_a_builtin(cur_mat->cmd) >= 0)
	{
		in = dup(0);
		out = dup(1);
		ft_modi_child_fd(msh, cur_mat, i);
		dup2(in, 0);
		dup2(out, 1);
		close(in);
		close(out);
		return ;
	}
	else
		execute_cmd_by_pipe2(msh, cur_mat, i);
}

void	processing_each_cmd(t_msh *msh)
{
	int			i;
	t_exec_mat	*cur_mat;

	i = -1;
	set_t_msh_before_exec_cmd(msh);
	while (++ i <= msh->pipe_cnt)
		execute_cmd_by_pipe(msh, i);
	if (msh->tmp_fd >= 0)
		close(msh->tmp_fd);
	cur_mat = &msh->ex_mat[i - 1];
	if (msh->pipe_cnt != 0 || is_cmd_a_builtin(cur_mat->cmd) < 0)
	{
		waitpid(cur_mat->pid, &msh->stat, 0);
		msh->exit_code = WEXITSTATUS(msh->stat);
		if (g_c_signal == 130 || g_c_signal == 131)
		{
			msh->exit_code = g_c_signal;
			g_c_signal = 0;
		}
		while (-- i >= -1)
			wait(0);
		signal_initial_parent();
	}
}
