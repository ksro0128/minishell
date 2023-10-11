/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc_and_tmp_file_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:25:09 by surkim            #+#    #+#             */
/*   Updated: 2023/10/05 13:08:00 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*make_tmp_file(void)
{
	int		i;
	char	*i_str;
	char	*file_name;

	i = 0;
	while (i < INT_MAX)
	{
		i_str = ft_itoa(i);
		file_name = ft_strjoin("/tmp/.tmp", i_str);
		free(i_str);
		if (access(file_name, F_OK) == -1)
			return (file_name);
		free(file_name);
		i ++;
	}
	exit(1);
}

char	*apply_env_str(char *str, t_msh *msh)
{
	int		s;
	int		i;
	char	*rt;

	s = 0;
	i = 0;
	rt = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			rt = ft_strjoin_12free(rt, cut_s_to_i(str, s, i));
			rt = ft_strjoin_12free(rt, extract_env(str, &i, msh));
			s = i + 1;
		}
		i++;
	}
	rt = ft_strjoin_12free(rt, cut_s_to_i(str, s, i));
	free(str);
	return (rt);
}

void	make_heredoc_applied_env(int fd, char *tmp_file, \
		char *limiter, t_msh *msh)
{
	char	*line;

	while (TRUE)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf("\033[A> ");
			exit(2);
		}
		if (ft_strncmp(limiter, line, ft_strlen(limiter) + 1) == 0)
		{
			free(limiter);
			free(line);
			close(fd);
			return ;
		}
		line = apply_env_str(line, msh);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	make_heredoc_not_applied_env(int fd, char *tmp_file, char *limiter)
{
	char	*line;

	while (TRUE)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf("\033[A> ");
			exit(2);
		}
		if (ft_strncmp(limiter, line, ft_strlen(limiter) + 1) == 0)
		{
			free(limiter);
			free(line);
			close(fd);
			return ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

char	*merge_token_to_str(t_env_tmp *head)
{
	char	*rt;

	rt = ft_strdup("");
	head = head->next;
	while (head)
	{
		rt = ft_strjoin_1free(rt, head->str);
		head = head->next;
	}
	return (rt);
}
