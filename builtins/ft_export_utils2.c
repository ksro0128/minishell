/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:54:33 by surkim            #+#    #+#             */
/*   Updated: 2023/10/05 12:52:52 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sorting_env(t_env *env_list)
{
	int		i;
	int		j;
	int		cnt;
	t_env	*head;

	env_list = env_list->next;
	cnt = get_env_list_size(env_list);
	head = env_list;
	i = 0;
	while (i < cnt)
	{
		env_list = head;
		j = i;
		while (j < cnt)
		{
			if (ft_strncmp(env_list->key, env_list->next->key, \
			ft_strlen(env_list->key) + 1) > 0)
				swap_env(env_list);
			env_list = env_list->next;
			j++;
		}
		i++;
	}
}

char	*get_key_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (cut_s_to_i(str, 0, i));
		i++;
	}
	return (cut_s_to_i(str, 0, i));
}

int	check_key(char *str)
{
	int	i;

	i = 1;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (-1);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (-1);
		i++;
	}
	return (1);
}

char	*get_value_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (ft_strdup(""));
	else
		return (cut_s_to_i(str, i + 1, ft_strlen(str)));
}
