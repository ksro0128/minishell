/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc_and_tmp_file_utils2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:28:22 by surkim            #+#    #+#             */
/*   Updated: 2023/10/04 16:49:23 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_heredoc2(int fd, pid_t pid, char *lim, t_msh *msh)
{
	close(fd);
	signal_ignore_parent(SIG_HERE);
	waitpid(pid, &msh->stat, 0);
	msh->stat = WEXITSTATUS(msh->stat);
	signal_initial_parent();
	free(lim);
}

char	*make_heredoc3(t_msh *msh, char *tmp_file)
{
	if (msh->stat == 1)
	{
		msh->exit_code = 1;
		unlink(tmp_file);
		free(tmp_file);
		return (NULL);
	}
	return (tmp_file);
}

void	make_heredoc_prev(int *fd, int *pid, char **tmp_file)
{
	*tmp_file = make_tmp_file();
	*fd = open(*tmp_file, O_WRONLY | O_CREAT);
	*pid = fork();
}

char	*make_heredoc(char *limiter, t_msh *msh)
{
	int		fd;
	pid_t	pid;
	char	*tmp_file;
	char	*lim;

	make_heredoc_prev(&fd, &pid, &tmp_file);
	lim = remove_quotes_str(limiter);
	if (pid > 0)
	{
		make_heredoc2(fd, pid, lim, msh);
		return (make_heredoc3(msh, tmp_file));
	}
	else if (pid == 0)
	{
		signal_setting_child(SIG_HERE);
		if (check_limiter(limiter))
			make_heredoc_applied_env(fd, tmp_file, lim, msh);
		else
			make_heredoc_not_applied_env(fd, tmp_file, lim);
		exit(0);
	}
	else
		exit(1);
}
