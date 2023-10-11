/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:56:35 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putunbr_fd(unsigned int n, int fd)
{
	int				idx;
	char			arr[10];

	idx = 10;
	if (!n)
		return (write(fd, "0", 1));
	while (n != 0)
	{
		idx --;
		arr[idx] = n % 10 + '0';
		n /= 10;
	}
	return (write(fd, arr + idx, 10 - idx));
}
