/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmdline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:54:35 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/05 13:08:02 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_cmdline(t_msh *msh)
{
	char	*cmd;

	cmd = readline("minishell$ ");
	if (cmd == NULL)
	{
		printf("\033[Aminishell$ exit\n");
		exit(msh->exit_code);
	}
	if (cmd[0] == '\0')
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}
