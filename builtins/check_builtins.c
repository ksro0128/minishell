/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:10:16 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/04 16:10:39 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cmd_a_builtin(char *cmd)
{
	int		ret;

	ret = NOT_BLTIN;
	if (cmd == NULL)
		return (NULLCMD);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		ret = B_CD;
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		ret = B_ECHO;
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ret = B_ENV;
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		ret = B_EXIT;
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ret = B_PWD;
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ret = B_UNSET;
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ret = B_EXPORT;
	return (ret);
}

int	exec_builtin(t_msh *msh, t_exec_mat *mat, char **env, int i)
{
	int		ret;
	char	*cmd;

	ret = NOT_BLTIN;
	cmd = mat->cmd;
	if (cmd == NULL)
		return (NULLCMD);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		ret = ft_cd(msh, mat->arg, msh->env_list);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		ret = ft_echo(msh, mat->arg);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ret = ft_env(env);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		ret = ft_exit(msh, mat->arg);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ret = ft_pwd();
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ret = ft_unset(msh, mat->arg, msh->env_list);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ret = ft_export(msh, mat->arg, msh->env_list);
	if (ret != NOT_BLTIN && msh->pipe_cnt == i)
		close(msh->tmp_fd);
	return (ret);
}
