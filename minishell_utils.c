/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:26:19 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/25 09:37:04 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_white_space(int stat)
{
	if (stat == M_SPACE)
		return (TRUE);
	if (stat == M_TAB)
		return (TRUE);
	return (FALSE);
}

int	is_meta_char(char c, char *sepstr)
{
	int	i;
	int	str_len;

	i = 0;
	str_len = ft_strlen(sepstr);
	while (i < str_len)
	{
		if (c == sepstr[i])
			return (TRUE);
		i ++;
	}
	return (FALSE);
}

char	*ft_strjoin_1free(char *s1, char *s2)
{
	char	*s_join;
	int		idx1;
	int		idx2;

	idx1 = 0;
	idx2 = 0;
	while (s1[idx1])
		idx1 ++;
	while (s2[idx2])
	{
		idx1 ++;
		idx2 ++;
	}
	s_join = malloc(sizeof(char) * (idx1 + 1));
	if (!s_join)
		return (0);
	idx1 = -1;
	idx2 = -1;
	while (s1[++ idx1])
		s_join[idx1] = s1[idx1];
	while (s2[++ idx2])
		s_join[idx1 ++] = s2[idx2];
	s_join[idx1] = '\0';
	free(s1);
	return (s_join);
}

char	*ft_strjoin_2free(char *s1, char *s2)
{
	char	*s_join;
	int		idx1;
	int		idx2;

	idx1 = 0;
	idx2 = 0;
	while (s1[idx1])
		idx1 ++;
	while (s2[idx2])
	{
		idx1 ++;
		idx2 ++;
	}
	s_join = malloc(sizeof(char) * (idx1 + 1));
	if (!s_join)
		return (0);
	idx1 = -1;
	idx2 = -1;
	while (s1[++ idx1])
		s_join[idx1] = s1[idx1];
	while (s2[++ idx2])
		s_join[idx1 ++] = s2[idx2];
	s_join[idx1] = '\0';
	free(s2);
	return (s_join);
}

char	*ft_strjoin_12free(char *s1, char *s2)
{
	char	*rt;

	rt = ft_strjoin_1free(s1, s2);
	free(s2);
	return (rt);
}
