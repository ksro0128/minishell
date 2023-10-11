/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:18:12 by surkim            #+#    #+#             */
/*   Updated: 2023/10/05 13:26:05 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	t_env_len(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		env = env->next;
		len ++;
	}
	return (len);
}

t_env	*create_env_token(char *key, char *value)
{
	t_env	*rt;

	rt = (t_env *)malloc(sizeof (t_env));
	if (rt == NULL)
		exit(1);
	rt->key = key;
	rt->value = value;
	rt->next = NULL;
	return (rt);
}

char	*ft_cut(const char *str, int idx)
{
	char	*rt;
	int		i;

	rt = (char *)malloc(sizeof (char) * (idx + 1));
	if (rt == NULL)
		exit(1);
	i = 0;
	while (i < idx)
	{
		rt[i] = str[i];
		i++;
	}
	rt[i] = '\0';
	return (rt);
}

void	line_to_token(t_env *head, char *str)
{
	int		i;
	char	*key;
	char	*value;

	while (head->next)
		head = head->next;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	value = ft_strdup(str + i + 1);
	key = ft_cut(str, i);
	head->next = create_env_token(key, value);
}

t_env	*get_env(char *env[])
{
	t_env	*head;
	int		i;

	head = create_env_token(NULL, NULL);
	i = 0;
	while (env[i])
	{
		line_to_token(head, env[i]);
		i++;
	}
	return (head);
}
