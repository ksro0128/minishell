/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:48:10 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/04 15:38:03 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token(t_token *token, int stat, char *str)
{
	if (token == NULL)
		return ;
	token->stat = stat;
	if (token->str)
		free(token->str);
	token->str = str;
	token->str_len = ft_strlen(str);
}

t_token	*create_token(char *str, int stat)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		exit(1);
	ft_memset(token, 0, sizeof(t_token));
	set_token(token, stat, str);
	token->next = NULL;
	return (token);
}

void	add_token(t_token *head, char *str, int idx, int stat)
{
	char	*token;
	int		size;
	int		i;

	if (idx == 0)
		return ;
	while (head->next)
		head = head->next;
	size = idx + 1;
	token = (char *)malloc(sizeof(char) * size);
	if (token == NULL)
		exit(1);
	i = 0;
	while (i < idx)
	{
		token[i] = str[i];
		i++;
	}
	token[i] = '\0';
	if (head->str == NULL)
		set_token(head, stat, token);
	else
		head->next = create_token(token, stat);
}

void	delete_all_token(t_token **head)
{
	t_token	*cur;
	t_token	*tmp;

	cur = *head;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		if (tmp->stat == F_HEREDOC)
			unlink(tmp->str);
		if (tmp->str != NULL)
			free(tmp->str);
		free(tmp);
	}
	*head = NULL;
}

void	print_token(t_token *head)
{
	while (head)
	{
		printf("[%s: %d] ==> ", head->str, head->stat);
		head = head->next;
	}
	printf("\n\n");
}
