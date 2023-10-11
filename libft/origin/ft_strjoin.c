/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:26:19 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
	return (s_join);
}
