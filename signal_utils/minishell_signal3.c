/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:55:56 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/04 17:07:24 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigact_setting_child_heredoc(int signo, siginfo_t *info, void *pid)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		exit(1);
	}
	if (signo == SIGQUIT)
	{
		rl_redisplay();
	}
}

void	sigact_setting_child(int signo, siginfo_t *info, void *pid)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		exit(130);
	}
	if (signo == SIGQUIT)
	{
		rl_redisplay();
	}
}

void	signal_setting_child(int flag)
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, SIGINT);
	sigaddset(&sigact.sa_mask, SIGQUIT);
	if (flag == SIG_HERE)
		sigact.sa_sigaction = &sigact_setting_child_heredoc;
	else if (flag == SIG_CMD)
		sigact.sa_sigaction = &sigact_setting_child;
	sigaction(SIGINT, &sigact, NULL);
}
