/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:21:40 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/25 14:59:54 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_point(unsigned long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	else if (nb > 0)
	{
		len += ft_putstr("0x") + ft_lowerhex(nb);
	}
	return (len);
}
