/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:54:48 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/03/22 22:46:12 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str ++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str ++;
	}
	while ('0' <= *str && *str <= '9')
	{
		num *= 10;
		num += *str - '0';
		str ++;
	}
	return (num * sign);
}
