/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe_child.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:16:51 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/05 11:35:36 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**parsing_path_env(t_msh *msh)
{
	char	*path_value;
	char	**path_ret;

	path_value = find_env_value(msh->env_list, "PATH");
	if (path_value == NULL)
	{
		msh->path = NULL;
		return (NULL);
	}
	path_ret = ft_split(path_value, ':');
	free(path_value);
	return (path_ret);
}

int	make_absolute_path_cmd2(t_msh *msh, t_exec_mat *cur_mat, char *cmd)
{
	int		i;
	char	*final_cmd;

	i = -1;
	while (msh->path && msh->path[++ i])
	{
		final_cmd = ft_strjoin(msh->path[i], cmd);
		if (!access(final_cmd, F_OK) && !access(final_cmd, X_OK))
		{
			free(cmd);
			free(cur_mat->cmd);
			cur_mat->cmd = final_cmd;
			return (SUCCESS);
		}
		free(final_cmd);
	}
	return (ERROR);
}

int	make_absolute_path_cmd(t_msh *msh, t_exec_mat *cur_mat)
{
	char	*cmd;

	if (cur_mat->cmd == NULL || cur_mat->cmd[0] == '\0')
		return (NULLCMD);
	if (!access(cur_mat->cmd, F_OK) || \
		ft_strncmp(cur_mat->cmd, "./", 2) == 0 || \
		ft_strncmp(cur_mat->cmd, "/", 1) == 0)
		return (SUCCESS);
	cmd = ft_strjoin("/", cur_mat->cmd);
	if (make_absolute_path_cmd2(msh, cur_mat, cmd) == SUCCESS)
		return (SUCCESS);
	free(cmd);
	handling_error(msh, E_CMDNF, cur_mat->cmd, NULL);
	return (ERROR);
}

void	ft_execve(t_msh *msh, char *cmd, char **arg, char **env)
{
	execve(cmd, arg, env);
	if (strncmp(cmd, "./", 2) != 0 && strncmp(cmd, "/", 1) != 0)
		handling_error(msh, E_CMDNF, cmd, NULL);
	else
		handling_error(msh, E_OTHER, cmd, NULL);
	exit(msh->exit_code);
}

int	ft_modi_child_fd(t_msh *msh, t_exec_mat *cur_mat, int i)
{
	int		is_builtin;
	char	**env;

	env = make_t_env_to_envp(msh->env_list);
	if (find_in_out_file(msh, cur_mat, i) == ERROR)
		return (1);
	close(msh->pipe_fd[FD_RD]);
	dup2(cur_mat->fd_in, FD_RD);
	dup2(cur_mat->fd_out, FD_WR);
	if (cur_mat->fd_in != FD_RD)
		close(cur_mat->fd_in);
	close(msh->pipe_fd[FD_WR]);
	is_builtin = exec_builtin(msh, cur_mat, env, i);
	if (is_builtin == NOT_BLTIN && \
		make_absolute_path_cmd(msh, cur_mat) == ERROR)
		exit (msh->exit_code);
	else if (is_builtin == NOT_BLTIN && cur_mat->cmd != NULL)
		ft_execve(msh, cur_mat->cmd, cur_mat->arg, env);
	free_strs(env);
	return (0);
}
