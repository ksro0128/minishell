/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:01:52 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/11 12:39:12 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_valid_option(char *arg)
{
	int	i;

	if (arg == NULL)
		return (ERROR);
	if (ft_strncmp(arg, "-n", 2) == SUCCESS)
	{
		i = 2;
		while (arg[i])
		{
			if (arg[i] != arg[1])
				return (ERROR);
			i ++;
		}
		return (SUCCESS);
	}
	return (ERROR);
}

int	ft_echo(t_msh *msh, char **arg)
{
	int		i;
	int		last_newline;

	i = 1;
	last_newline = check_valid_option(arg[i]);
	while (last_newline == SUCCESS)
		last_newline = check_valid_option(arg[++ i]);
	if (i != 1)
		last_newline = SUCCESS;
	if (arg[i])
	{
		printf("%s", arg[i]);
		i ++;
		while (arg[i])
		{
			printf(" %s", arg[i]);
			i ++;
		}
	}
	if (last_newline == ERROR)
		printf("\n");
	msh->exit_code = SUCCESS;
	return (SUCCESS);
}
