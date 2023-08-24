/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:18:03 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/24 18:42:48 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quotes(char *s)
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