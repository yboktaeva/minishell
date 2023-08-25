/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:18:03 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/25 19:18:13 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quotes(char *s, int *i)
{
    int single_quote_counter = 0;
    int double_quote_counter = 0;
    
    single_quote_counter = 0;
    double_quote_counter = 0;
    if (s[*i] == '\0')
    {
        if (single_quote_counter % 2 != 0 || double_quote_counter % 2 != 0)
            return (-1);
        else
            return (0);
    }
    if (s[*i] == '\'')
        single_quote_counter++;
    if (s[*i] == '\"')
        double_quote_counter++;
    (*i)++;
    return (check_quotes(s, i));
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

// void remove_same_quotes(char *s)
// {
//     int i;
//     int j;
//     int len;
//     int quote; 

//     i = 0;
//     j = 0;
//     quote = 0;
//     len = ft_strlen(s);
//     char temp[len + 1];
//     //remove_empty_quotes(s);
//     while (i < len)
//     {
//         if (s[i] == '\'' || s[i] == '\"')
//         {
//             if (quote == 0)
//             {
//                 quote = s[i];
//                 temp[j++] = s[i];
//             }
//             else if (s[i] == quote && (s[i + 1] == ' ' || s[i + 1] == '\0' || s[i + 1] == '\'' || s[i + 1] == '\"'))
//             {
//                 quote = 0;
//                 temp[j++] = s[i];
//             }
//             // else if (quote != 0 && s[i] != quote)
//             //     temp[j++] = s[i];          
//         }
//         else
//             temp[j++] = s[i];
//         i++;
//     }
//     temp[j] = '\0';
//     ft_strcpy(s, temp);
// }