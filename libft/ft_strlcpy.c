/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:14:59 by yuboktae          #+#    #+#             */
/*   Updated: 2022/11/10 13:50:13 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
	dst[i] = '\0';
	}
	return (j);
}
/*int   main()
{
        char src[] = "Hello";
        char dst[] = "Moule";
        printf("%ld %s\n", ft_strlcpy(dst, src, 5), dst);
        char src1[] = "Hello";
        char dst1[] = "Moule";
        printf("%ld %s\n", strlcpy(dst1, src1, 5), dst1);
}
*/