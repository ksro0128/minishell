/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:50:31 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/11 11:02:27 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_exitcode(t_msh *msh, int errnum)
{
	if (errnum == E_SYNTAX)
		msh->exit_code = 258;
	else if (errnum == E_NAN)
		msh->exit_code = 255;
	else if (errnum == E_CMDNF)
		msh->exit_code = 127;
	else if (errno == 13)
		msh->exit_code = 126;
	else
		msh->exit_code = ERROR;
}

char	*mk_msg(char *fst, char *snd, char *trd, char *fth)
{
	char	*msg;

	msg = fst;
	if (snd != NULL)
		msg = ft_strjoin(fst, snd);
	if (msg == NULL)
		exit(1);
	if (trd != NULL)
		msg = ft_strjoin_1free(msg, trd);
	if (msg == NULL)
		exit(1);
	if (fth != NULL)
		msg = ft_strjoin_1free(msg, fth);
	if (msg == NULL)
		exit(1);
	return (msg);
}

void	print_msg(char *fst, char *snd, char *trd, char *fth)
{
	char	*msg;

	msg = ft_strdup(fst);
	if (snd != NULL)
		msg = ft_strjoin_1free(msg, snd);
	if (msg == NULL)
		exit(1);
	if (trd != NULL)
		msg = ft_strjoin_1free(msg, trd);
	if (msg == NULL)
		exit(1);
	if (fth != NULL)
		msg = ft_strjoin_1free(msg, fth);
	if (msg == NULL)
		exit(1);
	ft_putendl_fd(msg, 2);
	free(msg);
}

int	handling_error2(t_msh *msh, int errnum, char *fst_str, char *snd_str)
{
	char	*msg;
	char	*strerr;

	if (errnum == E_AMBIG)
		print_msg("minishell: ", fst_str, ": ambiguous redirect", NULL);
	else if (errnum == E_NVALID)
		print_msg("minishell: export: `", fst_str, "': not a valid identifier", \
		NULL);
	else if (errnum == E_QUOTE)
		print_msg("minishell: wrong quotes in command", NULL, NULL, NULL);
	else if (errnum == E_TWOARG)
	{
		strerr = strerror(errno);
		msg = mk_msg("minishell: ", fst_str, ": ", snd_str);
		print_msg(msg, ": ", strerr, NULL);
		free(msg);
	}
	else
	{
		strerr = strerror(errno);
		print_msg("minishell: ", fst_str, ": ", strerr);
	}
	if (errnum == E_OPEN || errnum == E_AMBIG)
		return (FD_ERROR);
	return (msh->exit_code);
}

int	handling_error(t_msh *msh, int errnum, char *fst_str, char *snd_str)
{
	char	*msg;

	set_exitcode(msh, errnum);
	if (errnum == E_SYNTAX)
		print_msg("minishell: syntax error near unexpected token `", \
		fst_str, "'", NULL);
	else if (errnum == E_ENVSET)
	{
		msg = mk_msg("minishell: ", fst_str, ": ", snd_str);
		print_msg(msg, " not set", NULL, NULL);
		free(msg);
	}
	else if (errnum == E_TOMANY)
		print_msg("minishell: ", fst_str, ": too many arguments", NULL);
	else if (errnum == E_NAN)
	{
		msg = mk_msg("minishell: ", fst_str, ": ", snd_str);
		print_msg(msg, ": numeric argument required", NULL, NULL);
		free(msg);
	}
	else if (errnum == E_CMDNF)
		print_msg("minishell: ", fst_str, ": command not found", NULL);
	else
		return (handling_error2(msh, errnum, fst_str, snd_str));
	return (msh->exit_code);
}
