/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:11:08 by surkim            #+#    #+#             */
/*   Updated: 2023/10/05 12:55:17 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sorting_printing_env(t_env *env_list)
{
	t_env	*copy_env_list;

	copy_env_list = copy_env(env_list);
	sorting_env(copy_env_list);
	print_export(copy_env_list);
	free_copy_env_list(copy_env_list);
}

void	change_or_add(t_env *env_list, char *key, char *value)
{
	if (env_list->next)
		env_list = env_list->next;
	while (env_list->next)
	{
		if (ft_strncmp(key, env_list->key, ft_strlen(key) + 1) == 0)
		{
			free(env_list->value);
			env_list->value = value;
			free(key);
			return ;
		}
		env_list = env_list->next;
	}
	if (env_list->key != NULL \
	&& ft_strncmp(key, env_list->key, ft_strlen(key) + 1) == 0)
	{
		free(env_list->value);
		env_list->value = value;
		free(key);
		return ;
	}
	env_list->next = create_env_token(key, value);
}

int	change_or_add_env(t_env *env_list, char *str)
{
	char	*key;
	char	*value;

	key = get_key_str(str);
	if (check_key(key) < 0)
	{
		free(key);
		return (ERROR);
	}
	value = get_value_str(str);
	change_or_add(env_list, key, value);
	return (SUCCESS);
}

int	ft_export(t_msh *msh, char **arg, t_env *env_list)
{
	int		i;
	int		flag;

	if (arg[1] == NULL)
	{
		sorting_printing_env(env_list);
		return (SUCCESS);
	}
	i = 1;
	flag = 0;
	while (arg[i])
	{
		if (change_or_add_env(env_list, arg[i]) == ERROR)
			flag = handling_error(msh, E_NVALID, arg[i], NULL);
		i++;
	}
	return (flag);
}
