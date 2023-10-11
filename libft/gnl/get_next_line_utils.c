/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 13:43:41 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/19 15:50:18 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_make_alloc(size_t len, char *src, size_t st_idx, int flag)
{
	char	*str;
	size_t	idx;

	idx = 0;
	if (flag)
		str = (char *) malloc(sizeof(char) * (len + 1));
	else
		str = (char *) malloc(sizeof(char) * (len));
	if (!str)
		return (0);
	while (idx < len)
	{
		str[idx] = src[st_idx + idx];
		idx ++;
	}
	if (flag)
		str[len] = '\0';
	return (str);
}

char	*ft_strdup2(t_gnl *node, char *buf, size_t len, int flag)
{
	char	*s2;
	char	*tmp;

	free(buf);
	if (!len)
		return (0);
	s2 = ft_make_alloc(len, node->buf, 0, 1);
	tmp = ft_make_alloc(node->buf_len - len, node->buf, len, 0);
	if (!tmp || !s2)
	{
		free(tmp);
		free(s2);
		return (0);
	}
	free(node->buf);
	node->buf = tmp;
	node->buf_len -= len;
	if (!flag)
		node->flag = 0;
	return (s2);
}

int	ft_strjoin_gnl(t_gnl *node, char const *s2, ssize_t read_tmp)
{
	char	*s_join;
	size_t	idx1;
	ssize_t	idx2;

	s_join = malloc(sizeof(char) * (node->buf_len + read_tmp));
	if (!s_join)
		return (0);
	idx1 = 0;
	idx2 = 0;
	while (idx1 < node->buf_len)
	{
		s_join[idx1] = node->buf[idx1];
		idx1 ++;
	}
	node->buf_len += read_tmp;
	while (idx2 < read_tmp)
	{
		s_join[idx1 ++] = s2[idx2];
		idx2 ++;
	}
	free(node->buf);
	node->buf = s_join;
	return (1);
}
