/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:12:03 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/28 12:23:10 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;

	if (nmemb * size / size != nmemb)
		return (NULL);
	s = (void *)malloc(nmemb * size);
	if (!s)
		return (NULL);
	ft_bzero(s, nmemb * size);
	return (s);
}
/*
int main(void)
{
    long *s;

    s = (long *)ft_calloc(40, sizeof(long));
    if (s != NULL)
        printf("Allocated 40 long integers\n");
    else
        printf("Can't allocate memory\n");
    free(s);
}
*/
