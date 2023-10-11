/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:51:02 by surkim            #+#    #+#             */
/*   Updated: 2023/10/04 15:53:12 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*copy_env(t_env *env_list)
{
	t_env	*head;
	t_env	*rt;

	head = create_env_token(NULL, NULL);
	rt = head;
	env_list = env_list->next;
	while (env_list)
	{
		head->next = create_env_token(ft_strdup(env_list->key), \
		ft_strdup(env_list->value));
		head = head->next;
		env_list = env_list->next;
	}
	return (rt);
}

void	swap_env(t_env *token)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = token->key;
	tmp_value = token->value;
	token->key = token->next->key;
	token->value = token->next->value;
	token->next->key = tmp_key;
	token->next->value = tmp_value;
}

int	get_env_list_size(t_env *env_list)
{
	int	cnt;

	cnt = -1;
	while (env_list)
	{
		env_list = env_list->next;
		cnt++;
	}
	return (cnt);
}

void	print_export(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->key != NULL)
			printf("declare -x %s=\"%s\"\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}

void	free_copy_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
