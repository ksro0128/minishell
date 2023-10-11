/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:27:01 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s_ptr;
	size_t	idx;

	idx = 0;
	while (s[idx] && idx < start)
		idx ++;
	if (idx < start)
		return (ft_calloc(1, 1));
	idx = 0;
	while (idx < len && s[idx + start])
		idx ++;
	s_ptr = malloc(sizeof(char) * (idx + 1));
	if (!s_ptr)
		return (0);
	s_ptr[idx] = '\0';
	while (idx)
	{
		s_ptr[idx - 1] = s[start + idx - 1];
		idx --;
	}
	return (s_ptr);
}
/*
#include <stdio.h>

int main(int ac, char **av)
{
	(void) ac;
	printf("%s_", ft_substr(av[1], atoi(av[2]), atoi(av[3])));
}
*/