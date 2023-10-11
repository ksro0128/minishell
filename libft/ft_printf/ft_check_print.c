/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:08:22 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/19 16:01:32 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_check_print(int fd, const char *s, va_list *ap)
{
	int	val;

	val = 0;
	if (*s == 'c')
		val = ft_putchar_fd(va_arg(*ap, int), fd);
	else if (*s == 's')
		val = ft_putstr_fd(va_arg(*ap, char *), fd);
	else if (*s == 'p')
		ft_putaddr_fd(va_arg(*ap, unsigned long long int), &val, 0, fd);
	else if (*s == 'd' || *s == 'i')
		val = ft_putnbr_fd(va_arg(*ap, int), fd);
	else if (*s == 'u')
		val = ft_putunbr_fd(va_arg(*ap, int), fd);
	else if (*s == 'x')
		ft_puthexa_fd(va_arg(*ap, unsigned int), &val, -1, fd);
	else if (*s == 'X')
		ft_puthexa_fd(va_arg(*ap, unsigned int), &val, 1, fd);
	else if (*s == '%')
		val = write(1, "%%", fd);
	else
		val = -2;
	return (val);
}
