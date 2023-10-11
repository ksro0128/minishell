/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:31:45 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*us1;
	const unsigned char	*us2;
	size_t				chk;

	us1 = (const unsigned char *)s1;
	us2 = (const unsigned char *)s2;
	chk = 0;
	if (n == 0)
		return (0);
	while (chk + 1 < n && us1[chk] && us1[chk] == us2[chk])
		chk ++;
	return (us1[chk] - us2[chk]);
}
