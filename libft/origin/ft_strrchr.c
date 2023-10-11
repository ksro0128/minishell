/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:30:54 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/03/14 20:39:01 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr_s;
	char	ch;

	ptr_s = 0;
	ch = (char) c;
	while (*s)
	{
		if (*s == ch)
			ptr_s = (char *)s;
		s ++;
	}
	if (*s == ch)
		ptr_s = (char *)s;
	return (ptr_s);
}
