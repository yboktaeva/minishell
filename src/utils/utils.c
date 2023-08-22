/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:35:01 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/22 20:10:08 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <stdlib.h>

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t	i;
	
	i = 0;
    while (i < n && src[i] != '\0')
	{
        dest[i] = src[i];
		i++;
    }
    while (i < n)
	{
        dest[i] = '\0';
		i++;
	}
    return (dest);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	size_t	len;
	char	*ret;

	i = 0;
	len = 0;
	while (len < n && s[len])
		len++;
	ret = (char *)malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	if (arr == NULL)
		return (0);
	while (arr[i] != NULL)
		i++;
	return (i);
}