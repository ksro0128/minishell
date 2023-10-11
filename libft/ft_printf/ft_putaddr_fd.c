/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:57:36 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putaddr_fd(unsigned long long int num, int *val, int len, int fd)
{
	char	*hex;
	int		hexa_num;
	int		idx;

	idx = 0;
	if (!num)
	{
		if (len == 0)
			idx = write(fd, "0x0", 3);
		else
			idx = write(fd, "0x", 2);
	}
	else
	{
		hex = "0123456789abcdef";
		ft_putaddr_fd(num / 16, val, len + 1, fd);
		if (*val == -1)
			return ;
		hexa_num = num % 16;
		idx = write(fd, &hex[hexa_num], 1);
	}
	if (idx == -1)
		*val = idx;
	else
		*val += idx;
}
