/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:46:56 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_is_set(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set ++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		idx;
	char	*s_trim;

	idx = 0;
	if (!(*s1))
		return (ft_calloc(1, 1));
	while (ft_is_set(*s1, (char *)set) && *s1)
		s1 ++;
	while (s1[idx])
		idx ++;
	while (ft_is_set(*(s1 + idx - 1), (char *)set) && idx > 0)
		idx --;
	s_trim = (char *)malloc(sizeof(char) * (idx + 1));
	if (!s_trim)
		return (0);
	s_trim[idx] = '\0';
	while (idx > 0)
	{
		s_trim[idx - 1] = s1[idx - 1];
		idx --;
	}
	return (s_trim);
}
