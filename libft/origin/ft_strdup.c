/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:14:19 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/10/05 13:24:44 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	int		idx;
	char	*s2;

	idx = 0;
	while (s1[idx])
		idx ++;
	s2 = (char *) malloc(sizeof(char) * (idx + 1));
	if (!s2)
		return (0);
	idx = -1;
	while (s1[++ idx])
		s2[idx] = s1[idx];
	s2[idx] = '\0';
	return (s2);
}
