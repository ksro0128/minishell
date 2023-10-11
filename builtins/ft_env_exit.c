/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:03:23 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/11 11:25:23 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_strs(char **strs)
{
	while (*strs)
	{
		printf("%s\n", *strs);
		strs ++;
	}
}

int	ft_env(char **env)
{
	print_strs(env);
	return (SUCCESS);
}

static int	ft_atoi_onebit(char *str)
{
	long long	num;
	long long	sign;
	int			idx;

	num = 0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str ++;
	while ('0' == *str)
		str ++;
	idx = 0;
	while ('0' <= str[idx] && str[idx] <= '9')
	{
		num *= 10;
		num += str[idx] - '0';
		idx ++;
	}
	num *= sign;
	if (idx > 11 || num < INT_MIN || num > INT_MAX || str[idx] != 0)
		return (-10);
	while (num < 0)
		num += 256;
	return ((int)num % 256);
}

int	ft_exit(t_msh *msh, char **arg)
{
	int	ret;
	int	len;

	if (msh->pipe_cnt == 0)
		ret = msh->exit_code;
	else
		ret = 0;
	len = 0;
	if (msh->pipe_cnt == 0)
		printf("exit\n");
	while (arg[len])
		len ++;
	if (len >= 2)
		ret = ft_atoi_onebit(arg[1]);
	if (ret < 0)
		ret = handling_error(msh, E_NAN, "exit", arg[1]);
	else if (len > 2)
	{
		ret = handling_error(msh, E_TOMANY, "exit", NULL);
		return (ret);
	}
	exit(ret);
}
