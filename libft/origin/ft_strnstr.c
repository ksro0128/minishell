/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:48:37 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ind;
	size_t	i;

	if (!(*needle))
		return ((char *)haystack);
	ind = 0;
	while (*haystack && ind < len)
	{
		i = 0;
		while (haystack[i] == needle[i] && needle[i] && ind + i < len)
			i ++;
		if (!needle[i])
			return ((char *)haystack);
		haystack ++;
		ind ++;
	}
	return (0);
}
