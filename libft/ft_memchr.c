/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:56:18 by yuboktae          #+#    #+#             */
/*   Updated: 2022/11/16 17:48:21 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((unsigned char *)s + i);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int main(int argc, const char *argv[])
{
char search[] = "TechOnTheNet";
char *ptr;

ptr = (char*)ft_memchr(search, 'N', strlen(search));
if (ptr != NULL) 
printf("Found 'N' at position %ld.\n", 1+(ptr-search));
else 
printf("'N' was not found.\n");

return 0;
}
*/
