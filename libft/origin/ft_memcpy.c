/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:03:50 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	idx;

	idx = 0;
	if (dst == src)
		return (dst);
	while (idx < n)
	{
		((char *)dst)[idx] = ((const char *)src)[idx];
		idx ++;
	}
	return (dst);
}
/*
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av)
{
	char str[] = "wsdhflsdkfhjlsdk";
	
	printf("%s_", memcpy(str, str, 5));
}
*/