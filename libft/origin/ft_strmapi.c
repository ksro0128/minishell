/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:16:35 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s_map;
	unsigned int	idx;

	idx = 0;
	while (s[idx])
		idx ++;
	s_map = malloc(sizeof(char) * (idx + 1));
	if (!s_map)
		return (0);
	idx = 0;
	while (s[idx])
	{
		s_map[idx] = f(idx, s[idx]);
		idx ++;
	}
	s_map[idx] = '\0';
	return (s_map);
}
