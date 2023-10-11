/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:45:45 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int				sign;
	int				idx;
	char			arr[11];

	sign = 1;
	idx = 11;
	if (n < 0)
		sign = -1;
	else if (!n)
		return (write(fd, "0", 1));
	while (n != 0)
	{
		idx --;
		arr[idx] = (n % 10) * sign + '0';
		n /= 10;
	}
	if (sign < 0)
	{
		idx --;
		arr[idx] = '-';
	}
	return (write(fd, arr + idx, 11 - idx));
}
