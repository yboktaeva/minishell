/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:20:45 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/25 15:03:27 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdarg.h>

int	ft_printbase(const char *format, int len, va_list args)
{
	int	res;

	res = 0;
	if (format[len + 1] == 'c')
		res += ft_putchar(va_arg(args, int));
	else if (format[len + 1] == 's')
		res += ft_putstr(va_arg(args, char *));
	else if (format[len + 1] == 'd' || format[len + 1] == 'i')
		res += ft_putnbr(va_arg(args, int));
	else if (format[len + 1] == 'u')
		res += ft_unsign(va_arg(args, unsigned int));
	else if (format[len + 1] == 'x')
		res += ft_lowerhex(va_arg(args, unsigned int));
	else if (format[len + 1] == 'X')
		res += ft_upperhex(va_arg(args, unsigned int));
	else if (format[len + 1] == 'p')
		res += ft_point(va_arg(args, unsigned long));
	else if (format[len + 1] == '%')
		res += ft_putchar('%');
	return (res);
}
