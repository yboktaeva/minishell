/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:05:05 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/02 10:29:20 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int check_quotes(const char *s)
{
    int i;
    int flag;
    
    i = 0;
    flag = -1;
    while (s[i])
    {
        if (s[i] == '\'')
        {
            flag = 1;
            i++;
            while (s[i] && s[i] != '\'')
                i++;
            if (!s[i])
                flag = 0;
        }
        if (s[i] == '\"')
        {
            flag = 1;
            i++;
            while (s[i] && s[i] != '\"')
                i++;
            if (!s[i])
                flag = 0;
        }
        i++;
    }
    if (flag == 0)
        return (-1);
    return (0);
}

int	empty_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			return (1);
        i++;
	}
	return (0);
}

int check_input(char *line)
{
    int i;

    i = 0;
    if (line)
    {
        while (line[i])
        {
            if (line[i] == '\\' || line[i] == ';' || line[i] == '.' || (line[i] == '|' && line[i + 1] == '|'))
                return (-1);
            i++;
        }
    }
    return (0);
}