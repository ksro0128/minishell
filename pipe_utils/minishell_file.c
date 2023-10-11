/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:13:11 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/04 17:53:11 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_infile(t_msh *msh, t_token *token, int fd_in, int fd_out)
{
	if (fd_in != -10)
		close(fd_in);
	if (token->next->stat == F_AMBERR)
		return (handling_error(msh, E_AMBIG, token->next->str, NULL));
	fd_in = open(token->next->str, O_RDONLY);
	if (fd_in < 0)
	{
		if (fd_out > 0)
			close(fd_out);
		return (handling_error(msh, E_OPEN, token->next->str, NULL));
	}
	return (fd_in);
}

int	open_outfile(t_msh *msh, t_token *token, int fd_in, int fd_out)
{
	if (fd_out != -10)
		close(fd_out);
	if (token->next->stat == F_AMBERR)
		return (handling_error(msh, E_AMBIG, token->next->str, NULL));
	if (token->stat == F_REDIR_APP)
		fd_out = open(token->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (token->stat == F_REDIR_OUT)
		fd_out = open(token->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		if (fd_in > 0)
			close (fd_in);
		return (handling_error(msh, E_OPEN, token->next->str, NULL));
	}
	return (fd_out);
}

void	set_file_descriptor(t_msh *msh, t_exec_mat *cur_mat, int i)
{
	if (cur_mat->fd_in == -10)
		cur_mat->fd_in = msh->tmp_fd;
	if (cur_mat->fd_out == -10 || cur_mat->cmd == NULL)
		cur_mat->fd_out = msh->pipe_fd[FD_WR];
	if (i == msh->pipe_cnt && cur_mat->fd_out == msh->pipe_fd[FD_WR])
		cur_mat->fd_out = 1;
	if (cur_mat->fd_in == -2)
		cur_mat->fd_in = 0;
}

int	open_redir_file(t_msh *msh, t_exec_mat *cur_mat, t_token *token_list)
{
	int		*fd_in;
	int		*fd_out;
	int		token_stat;

	fd_in = &cur_mat->fd_in;
	fd_out = &cur_mat->fd_out;
	*fd_in = -10;
	*fd_out = -10;
	while (token_list)
	{
		token_stat = token_list->stat;
		if (token_stat == F_REDIR_IN)
			*fd_in = open_infile(msh, token_list, *fd_in, *fd_out);
		else if (token_stat == F_REDIR_OUT || token_stat == F_REDIR_APP)
			*fd_out = open_outfile(msh, token_list, *fd_in, *fd_out);
		if (*fd_in == FD_ERROR || *fd_out == FD_ERROR)
			return (ERROR);
		token_list = token_list->next;
	}
	return (SUCCESS);
}

int	find_in_out_file(t_msh *msh, t_exec_mat *cur_mat, int i)
{
	int		fd_in;
	int		fd_out;
	t_token	*token_list;

	token_list = cur_mat->token_list;
	fd_in = -10;
	fd_out = -10;
	if (open_redir_file(msh, cur_mat, token_list) == ERROR)
		return (ERROR);
	set_file_descriptor(msh, cur_mat, i);
	return (SUCCESS);
}
