/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:25:59 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/14 18:54:53 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!src)
		return (NULL);
	if (src <= dest)
	{
		while (n--)
		{
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
int	main()
{
	char src[] = "bonjour hello";
	char dest[] = "fhgrihg";
	ft_memmove(dest, src, ft_strlen(src)+1);
	printf("%s\n", dest);	
}
*/
