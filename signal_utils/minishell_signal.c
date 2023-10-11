/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:50:44 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/04 17:07:16 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_termios(t_msh *msh)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &msh->new_set);
}

void	unset_termios(t_msh *msh)
{
	msh->old_set.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &msh->old_set);
}

void	termios_initial_parent(t_msh *msh)
{
	struct termios		*old_set;
	struct termios		*new_set;

	old_set = &msh->old_set;
	new_set = &msh->new_set;
	tcgetattr(STDIN_FILENO, old_set);
	tcgetattr(STDIN_FILENO, new_set);
	new_set->c_lflag &= ~ECHOCTL;
}

void	set_signal_terminal_init(t_msh *msh)
{
	termios_initial_parent(msh);
	set_termios(msh);
	signal_initial_parent();
}
