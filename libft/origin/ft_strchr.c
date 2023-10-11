/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:24:26 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/03/14 16:06:58 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*ptr_s;
	char	ch;

	ptr_s = (char *) s;
	ch = (char) c;
	while (*ptr_s != ch && *ptr_s)
		ptr_s ++;
	if (*ptr_s == ch)
		return (ptr_s);
	else
		return ((void *) 0);
}
/*
#include <string.h>
#include <stdio.h>

int main(int ac, char **av)
{
	printf("%s_", ft_strchr(av[1], av[2][0]));
	printf("%s_", strchr(av[1], av[2][0]));
}
*/