/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:18:03 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/29 15:26:34 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_quotes(char *s)
{
    int i;
    int s_quote_count;
    int d_quote_count;
    
    i = 0;
    s_quote_count = 0;
    d_quote_count = 0;
    while (s[i])
    {
        if (s[i] == '\'')
            s_quote_count++;
        if (s[i] == '\"')
            d_quote_count++;
        i++;
    }
    if (s_quote_count % 2 != 0 || d_quote_count % 2 != 0)
        return (-1);
    else
        return (0);
}

void    remove_empty_quotes(char *s, int *i, int *j)
{
    if ((s[*i] == '\'' && s[*i + 1] == '\'') || (s[*i] == '\"' && s[*i + 1] == '\"'))
        (*i)++;
    else
        s[(*j)++] = s[*i];
    (*i)++;
    s[*j] = '\0';
}