/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:59:00 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_puthexa_fd(unsigned int num, int *val, int flag, int fd)
{
	char	*hex;
	int		hexa_num;
	int		idx;

	idx = 0;
	if (flag * flag == 1 && !num)
		idx = write(fd, "0", 1);
	else if (num)
	{
		if (flag < 0)
			hex = "0123456789abcdef";
		else if (flag > 0)
			hex = "0123456789ABCDEF";
		else
			return ;
		ft_puthexa_fd(num / 16, val, flag * 2, fd);
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
