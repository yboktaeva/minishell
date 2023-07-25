/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:16:05 by yuboktae          #+#    #+#             */
/*   Updated: 2022/11/21 14:16:26 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	void	*res;
	size_t	i;

	res = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		((unsigned char *)res)[i] = (unsigned char)c;
		i++;
	}
	return (res);
}
/*
int     main()
{
    char s[] = "Hello World";
    ft_memset(s, '+', 4);
    printf("%s\n", s);
	memset(s, '+', 4);
	printf("%s\n", s);
    return (0);
}
*/
