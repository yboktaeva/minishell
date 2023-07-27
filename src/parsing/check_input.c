/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:05:05 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/27 14:55:35 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int check_quotes(char *s)
{
    int i;
    int n;
    
    i = 0;
    n = 0;
    while (s[i])
    {
        if (s[i] == '\'')
            n++;
        i++;
    }
    if (n != 2)
        return (FAULSE);
    return (TRUE);
}

int check_double_quotes(char *s)
{
    int i;
    int n;
    
    i = 0;
    n = 0;
    while (s[i])
    {
        if (s[i] == '\"')
            n++;
        i++;
    }
    if (n != 2)
        return (FAULSE);
    return (TRUE);
}

int	empty_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			return (TRUE);
        i++;
	}
	return (FAULSE);
}