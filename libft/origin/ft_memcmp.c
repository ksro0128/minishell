/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:38:29 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				chk;
	const unsigned char	*c1;
	const unsigned char	*c2;

	chk = 0;
	c1 = (const unsigned char *) s1;
	c2 = (const unsigned char *) s2;
	if (n == 0)
		return (0);
	while (chk + 1 < n && c1[chk] == c2[chk])
		chk ++;
	return ((int)c1[chk] - (int)c2[chk]);
}
