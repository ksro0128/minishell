/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:50:34 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/04 17:07:20 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigact_setting_parent(int signo, siginfo_t *info, void *pid)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		g_c_signal = 130;
	}
	else if (signo == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		g_c_signal = 131;
	}
}

void	signal_ignore_parent(int flag)
{
	struct sigaction	sigact;

	if (flag == SIG_HERE)
	{
		sigact.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sigact, 0);
		sigaction(SIGQUIT, &sigact, 0);
	}
	else if (flag == SIG_CMD)
	{
		sigemptyset(&sigact.sa_mask);
		sigaddset(&sigact.sa_mask, SIGINT);
		sigaddset(&sigact.sa_mask, SIGQUIT);
		sigact.sa_sigaction = &sigact_setting_parent;
		sigaction(SIGINT, &sigact, NULL);
		sigaction(SIGQUIT, &sigact, NULL);
	}
}

void	sigact_initial_parent(int signo, siginfo_t *info, void *pid)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		rl_redisplay();
	}
}

void	signal_initial_parent(void)
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, SIGINT);
	sigaddset(&sigact.sa_mask, SIGQUIT);
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = &sigact_initial_parent;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
}
