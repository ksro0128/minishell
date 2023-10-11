/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:17:33 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/19 15:50:38 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_gnl	*ft_modify_fd(t_gnl **lst, t_gnl *new, int fd)
{
	t_gnl	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	new = (t_gnl *) malloc(sizeof(t_gnl));
	if (!new)
		return (0);
	new->fd = fd;
	new->flag = 1;
	new->buf = (void *) 0;
	new->buf_len = 0;
	new->next = (void *) 0;
	if (!tmp)
		*lst = new;
	else
		tmp->next = new;
	return (new);
}

char	*ft_loop_read(t_gnl *tmp, char *buf, size_t idx)
{
	ssize_t	read_tmp;

	while (tmp->flag)
	{
		while (tmp->buf && idx < tmp->buf_len && tmp->buf[idx] != '\n')
			idx ++;
		if (tmp->buf && idx < tmp->buf_len && tmp->buf[idx] == '\n')
			return (ft_strdup2(tmp, buf, idx + 1, 1));
		else
		{
			read_tmp = read(tmp->fd, buf, BUFFER_SIZE);
			if (read_tmp == 0 && tmp->flag == 1)
				return (ft_strdup2(tmp, buf, tmp->buf_len, 0));
			else if (read_tmp <= 0 || !ft_strjoin_gnl(tmp, buf, read_tmp))
				break ;
			else
				continue ;
		}
	}
	free(buf);
	return (0);
}

char	*ft_make_line(t_gnl *tmp)
{
	char	*buf;
	size_t	idx;

	idx = 0;
	buf = (char *) malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf)
		return (0);
	return (ft_loop_read(tmp, buf, idx));
}

void	ft_free_node(t_gnl **head, int fd)
{
	t_gnl	*prev_tmp;
	t_gnl	*tmp;

	tmp = *head;
	if (tmp->fd == fd)
	{
		*head = (*head)->next;
		free(tmp->buf);
		free(tmp);
		return ;
	}
	while (tmp->next)
	{
		prev_tmp = tmp;
		tmp = tmp->next;
		if (tmp->fd == fd)
		{
			prev_tmp->next = tmp->next;
			free(tmp->buf);
			free(tmp);
			tmp = prev_tmp->next;
			return ;
		}
	}
}

char	*get_next_line(int fd)
{
	static t_gnl	*head;
	t_gnl			*tmp;
	char			*line;

	tmp = 0;
	if (BUFFER_SIZE > SSIZE_SIZE || BUFFER_SIZE <= 0 || fd < 0)
		return ((void *) 0);
	tmp = ft_modify_fd(&head, tmp, fd);
	if (!tmp)
		return (0);
	line = ft_make_line(tmp);
	if (!line)
		ft_free_node(&head, fd);
	return (line);
}
