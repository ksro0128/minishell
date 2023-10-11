/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:45:38 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			idx;
	unsigned char	*ptr_s;
	unsigned char	ch;

	idx = 0;
	ptr_s = (unsigned char *) s;
	ch = (unsigned char) c;
	if (n == 0)
		return (0);
	while (ptr_s[idx] != ch && idx + 1 < n)
		idx ++;
	if (ptr_s[idx] == ch)
		return ((void *)(ptr_s + idx));
	else
		return (0);
}
