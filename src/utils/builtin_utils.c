/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:33:26 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/21 15:36:17 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stddef.h>

int str_check(char *str1, char *str2)
{
    if (!str1 || !str2)
        return (0);
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (0);
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
}

int	char_check(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i += 1;
	}
	return (0);
}
