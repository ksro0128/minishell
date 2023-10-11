/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:01:20 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/05 11:53:06 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_cd_special(t_msh *msh, char *path, t_env *env)
{
	char	*new_path;

	if (path == NULL)
	{
		new_path = find_env_value(env, "HOME");
		if (new_path == NULL)
		{
			handling_error(msh, E_ENVSET, "cd", "HOME");
			return (NULL);
		}
	}
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		new_path = find_env_value(env, "OLDPWD");
		if (new_path == NULL)
		{
			handling_error(msh, E_ENVSET, "cd", "OLDPWD");
			return (NULL);
		}
	}
	else
		new_path = ft_strdup(path);
	return (new_path);
}

int	ft_cd(t_msh *msh, char **arg, t_env *env)
{
	char	*new_path;
	char	*old_path;

	old_path = NULL;
	old_path = getcwd(old_path, 0);
	if (old_path == NULL)
	{
		handling_error(msh, E_TWOARG, "error retrieving current directory", \
		"getcwd: cannot access parent directories");
		exit(1);
	}
	old_path = ft_strjoin_12free(ft_strdup("OLDPWD="), old_path);
	new_path = ft_cd_special(msh, arg[1], env);
	change_or_add_env(msh->env_list, old_path);
	free(old_path);
	if (new_path == NULL)
		return (ERROR);
	if (chdir(new_path) != SUCCESS)
	{
		free(new_path);
		return (handling_error(msh, E_TWOARG, "cd", arg[1]));
	}
	free(new_path);
	return (SUCCESS);
}
