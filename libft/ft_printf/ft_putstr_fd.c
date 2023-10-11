/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:44:17 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_putstr_fd(char *s, int fd)
{
	ssize_t	tmp;
	ssize_t	size;

	tmp = 0;
	size = 0;
	if (!s)
		s = "(null)";
	while (size < (ssize_t)ft_strlen(s))
	{
		tmp = write(fd, s + size, ft_strlen(s) - size);
		if (tmp == -1)
			return (-1);
		size += tmp;
	}
	return (size);
}
