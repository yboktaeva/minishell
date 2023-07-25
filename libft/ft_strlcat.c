/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:15:10 by yuboktae          #+#    #+#             */
/*   Updated: 2022/11/29 14:13:47 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	l_dst;
	size_t	l_src;

	l_src = ft_strlen(src);
	if (!dst || !src)
		return (0);
	l_dst = ft_strlen(dst);
	if (size == 0)
		return (l_src);
	if (l_dst > size)
		return (size + l_src);
	i = 0;
	while ((src[i] != '\0') && (l_dst + i < size - 1))
	{
		dst[l_dst + i] = src[i];
		i++;
	}
	if (size > i)
		dst[l_dst + i] = '\0';
	return (l_dst + l_src);
}
/*
#include <stdio.h>
#include <bsd/string.h>
int   main()
{
	char src[] = "";
	char dst[] = "";
	printf("%ld\n", ft_strlcat(dst, src, 0));
	//printf("%ld\n", strlcat(dst, src, 0));
}
*/
