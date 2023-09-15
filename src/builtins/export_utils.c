/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:46:37 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/15 17:05:27 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int export_bad_id(char *id)
{
    printf("minishell: export: `%s': not a valid identifier\n", id);
    return (EXIT_FAILURE);
}

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

int	valid_id(char *str)
{
	size_t	i;

	i = 0;
	if (str_check(str, "="))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[i]) || str[i] == '!' || str[i] == '@'
			|| str[i] == '{' || str[i] == '}' || str[i] == '-')
			return (0);
		i += 1;
	}
	return (1);
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
