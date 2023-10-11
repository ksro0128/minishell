/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:54:45 by surkim            #+#    #+#             */
/*   Updated: 2023/10/04 17:29:22 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *head)
{
	head = head->next;
	while (head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}

char	*find_env_value(t_env *head, char *key)
{
	head = head->next;
	while (head)
	{
		if (ft_strncmp(head->key, key, ft_strlen(key) + 1) == 0)
			return (ft_strdup(head->value));
		head = head->next;
	}
	return (NULL);
}

t_env	*find_before_env(t_env *head, char *key)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
	{
		if (ft_strncmp(head->next->key, key, ft_strlen(key) + 1) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void	delete_key_env(t_env *head, char *key)
{
	t_env	*prev;
	t_env	*cur;

	prev = find_before_env(head, key);
	if (prev == NULL)
		return ;
	cur = prev->next;
	if (cur->next)
		prev->next = cur->next;
	else
		prev->next = NULL;
	free(cur->key);
	free(cur->value);
	free(cur);
}

char	**make_t_env_to_envp(t_env *env)
{
	int		i;
	int		len;
	char	**envp;

	i = 0;
	len = 0;
	len = t_env_len(env);
	envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (envp == NULL)
		exit(1);
	if (env == NULL)
		return (NULL);
	env = env->next;
	while (env)
	{
		envp[i] = ft_strjoin(env->key, "=");
		envp[i] = ft_strjoin_1free(envp[i], env->value);
		env = env->next;
		i ++;
	}
	envp[i] = NULL;
	return (envp);
}
