/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:45:50 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/05/25 20:19:42 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static unsigned int	intlen(int n, int *idx)
{
	unsigned int	un;
	int				sign;

	sign = 1;
	if (n < 0)
	{
		sign = -1;
		*idx += 1;
	}
	else if (n == 0)
	{
		*idx = 1;
		return (0);
	}
	un = n * sign;
	n = un / 10;
	*idx += 1;
	while (n)
	{
		n /= 10;
		*idx += 1;
	}
	return (un);
}

char	*ft_itoa(int n)
{
	char			*arr;
	unsigned int	un;
	int				idx;

	idx = 0;
	un = intlen(n, &idx);
	arr = malloc (sizeof(char) * (idx + 1));
	if (!arr)
		return (0);
	if (n < 0)
		arr[0] = '-';
	else if (n == 0)
		arr[0] = '0';
	arr[idx] = '\0';
	while (un)
	{
		idx --;
		arr[idx] = un % 10 + '0';
		un /= 10;
	}
	return (arr);
}
