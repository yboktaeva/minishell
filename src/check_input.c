/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:05:05 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/25 18:01:09 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int check_quotes(char *s)
{
    int i;

    i = 0;

    while (s[i])
    {
        if (s[i] == '\'')
        {
            if (s[i + 1] == '\'')
                return (1);
        }
        else if (s[i] =='\"')
        {
            if (s[i + 1] == '\"')
                return (1);
        }
        else
            return (0);
        i++;
    }
    return (0);
}