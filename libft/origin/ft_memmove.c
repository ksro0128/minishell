/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:03:28 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	idx;

	idx = 0;
	if (!dst && !src)
		return (dst);
	if (dst <= src)
	{
		while (idx < len)
		{
			((char *) dst)[idx] = ((char *) src)[idx];
			idx ++;
		}
	}
	else
	{
		while (idx < len)
		{
			((char *) dst)[len - 1] = ((char *) src)[len - 1];
			len --;
		}
	}
	return (dst);
}
