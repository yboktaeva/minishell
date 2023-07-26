/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:05:05 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/26 16:00:55 by yuboktae         ###   ########.fr       */
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
    if (n == 2)
        return (TRUE);
    return (FAULSE);
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
    if (n == 2)
        return (TRUE);
    return (FAULSE);
}