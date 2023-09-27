/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:36:33 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/27 15:52:15 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*ret;

	len = 0;
	if (!s)
		return (NULL);
	while (((char *)s)[len] != '\0')
		len++;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = ((char *)s)[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

/*#include <stdio.h>
int     main()
{
        char *s = "Coucou";
        char *ret = ft_strdup(s);
        printf("%s\n", ret);
        free(ret);
        return (0);
}
*/
