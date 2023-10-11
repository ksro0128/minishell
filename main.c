/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:47:05 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/11 11:38:14 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_cmd2(t_msh *msh, char *cmd)
{
	if (set_heredoc_and_tmp_file(msh->token_list, msh) == ERROR)
	{
		free(cmd);
		return (ERROR);
	}
	remove_white_space_token(&msh->token_list);
	redefine_status_of_token(msh->token_list);
	make_list_array(msh);
	free(cmd);
	return (SUCCESS);
}

int	parsing_cmd(t_msh *msh)
{
	char	*cmd;

	cmd = read_cmdline(msh);
	while (cmd == NULL)
		cmd = read_cmdline(msh);
	rl_redisplay();
	add_history(rl_line_buffer);
	if (check_valid_quotes(cmd) == ERROR)
	{
		free(cmd);
		return (handling_error(msh, E_QUOTE, NULL, NULL));
	}
	separate_by_quotes(&msh->token_list, cmd);
	separate_by_meta_char(&msh->token_list, C_META_CHAR);
	merge_except_meta_char(&msh->token_list);
	if (check_syntex_error(msh, msh->token_list, 0) != SUCCESS)
	{
		free(cmd);
		return (msh->exit_code);
	}
	return (parsing_cmd2(msh, cmd));
}

void	processing_cmd(t_msh *msh)
{
	int		i;

	i = 0;
	msh->pipe_cnt = -1;
	if (parsing_cmd(msh) == SUCCESS)
	{
		while (i <= msh->pipe_cnt)
		{
			applying_env(msh, &msh->ex_mat[i]);
			i ++;
		}
		unset_termios(msh);
		processing_each_cmd(msh);
		set_termios(msh);
		free_all_the_stuffs(msh);
	}
	else
		delete_all_token(&msh->token_list);
}

void	set_minishell(t_msh *msh, char **envp)
{
	msh->env_list = get_env(envp);
	msh->path = NULL;
	msh->ex_mat = NULL;
	msh->token_list = NULL;
	msh->pipe_cnt = -1;
	msh->exit_code = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	if (argc != 1)
		exit(1);
	argv = NULL;
	set_minishell(&msh, envp);
	set_signal_terminal_init(&msh);
	while (TRUE)
	{
		processing_cmd(&msh);
	}
	exit(0);
}
