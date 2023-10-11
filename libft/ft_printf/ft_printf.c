/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 10:45:58 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/19 16:32:51 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_check_percent(int fd, char *s, va_list *ap, int *tmp)
{
	int	val;

	if (*s == '%')
		val = ft_check_print(fd, s + 1, ap);
	else
		val = ft_putchar_fd(*s, fd);
	if (val == -1)
		*tmp = -1;
	else if (*s == '%')
	{
		if (val < -1)
		{
			if (ft_isdigit(*(s + 1)))
				val = ft_putchar_fd(' ', fd);
			else
				val = ft_putchar_fd(*(s + 1), fd);
		}
		s ++;
	}
	if (val != -1)
		*tmp += val;
	else
		*tmp = val;
	return (s);
}

int	ft_printf(const char *s, ...)
{
	int		tmp;
	int		size;
	va_list	ap;

	size = 0;
	va_start(ap, s);
	while (*s)
	{
		tmp = 0;
		s = ft_check_percent(1, (char *)s, &ap, &tmp);
		if (tmp == -1)
		{
			va_end(ap);
			return (-1);
		}
		size += tmp;
		s ++;
	}
	va_end(ap);
	return (size);
}

int	ft_fprintf(int fd, const char *s, ...)
{
	int		tmp;
	int		size;
	va_list	ap;

	size = 0;
	va_start(ap, s);
	while (*s)
	{
		tmp = 0;
		s = ft_check_percent(fd, (char *)s, &ap, &tmp);
		if (tmp == -1)
		{
			va_end(ap);
			return (-1);
		}
		size += tmp;
		s ++;
	}
	va_end(ap);
	return (size);
}
