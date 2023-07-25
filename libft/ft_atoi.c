/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:16:59 by yuboktae          #+#    #+#             */
/*   Updated: 2022/11/10 11:29:25 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (((s[i] >= 9 && s[i] <= 13) || s[i] == 32) && s[i])
		i++;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while ((s[i] >= '0' && s[i] <= '9') && s[i])
	{
		nb = nb * 10 + (s[i] - '0');
		i++;
	}
	return (nb * sign);
}

/*int	main(int argc, char **argv)
{
	int	myatoi;

	if (argc == 2)
	{
		myatoi = ft_atoi(argv[1]);
		printf("%d\n", myatoi);
	}
}
*/
