/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:59:20 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/14 19:10:29 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

t_type identify_token_type(const char *line)
{
    if (*line == '<')
    {
        if (*(line + 1) == '<')
            return (HEREDOC);
        else
           return (REDIR_IN);
    }
    else if (*line == '>')
    {
        if (*(line + 1) == '>')
            return (APPEND);
        else
            return (REDIR_OUT);
    }
    else if (*line == '|')
        return (PIPE);
    else
        return (WORD);
}

// void tokenize_input(const char *line, t_table *info)
// {
//     int     i;
//     int     len;
//     size_t  token_len;
//     size_t  operator_len;
//     int     count;
//     char    quote;
//     char    *tmp;
//     //char    *start;
    
//     i = 0;
//     count = 0;
//     quote = '\0';
//     len = ft_strlen(line);
//     tmp = ft_strdup(line);
//     operator_len = 0;
//     info->tok = malloc(sizeof(t_token) * (len + 1));
//     if (!info->tok)
//         exit (EXIT_FAILURE);
//     while (tmp[i])
//     {
//         if (identify_token_type(&tmp[i]) != WORD)
//         {
//             operator_len = 1;
//             if (identify_token_type(&tmp[i]) == HEREDOC || identify_token_type(&tmp[i]) == APPEND)
//                 operator_len = 2;
//             info->tok[count].value = ft_strndup(tmp, operator_len);
//             info->tok[count].type = identify_token_type(&tmp[i]);
//             count++;
//             i++;
//         }
//         //start = &tmp[i];
//         token_len = 0;
//         while (tmp[i] && !(ft_isspace(tmp[i]) && quote == '\0') && identify_token_type(&tmp[i]) == WORD)
//         {
//             if (tmp[i] == quote)
//                 quote = '\0';
//             else if ((tmp[i] == '\'' || tmp[i] == '\"') && quote == '\0')
//                 quote = tmp[i];
//             i++;
//             token_len++;
//         }
//         info->tok[count].value = ft_strndup(tmp, token_len);
//         info->tok[count].type = identify_token_type(info->tok[count].value);
//         count++;
//     }
// }
void tokenize_input(char *line, t_table *info)
{
    int count;
    int len;
    int i;
    
    i = 0;
    count = 0;
    len = ft_strlen(line);
    info->tok = malloc(sizeof(t_token) * (len + 1));
    if (!info->tok)
        exit (EXIT_FAILURE);
    while (i < len)
    {
        while (ft_isspace(line[i]))
            i++;
        if (line[i])
        {
            info->tok[count].type = identify_token_type(&line[i]);
            info->tok[count].value = &line[i];
            count++;
            while (line[i])
            {
                if (ft_isspace(line[i]))
                {
                    line[i] = '\0';
                    i++;
                    break ;
                }
                i++;
            }
        }
    }
    info->tok[count].value = NULL;
}
// void    error_handle(t_table *info)
// {
//     while (info->tok[info->count].value != NULL)
//     {
//         if (info->tok[info->count].type == INPUT && info->tok[info->count + 1].type != WORD)
        
//     }
// }
void    free_token(t_token *tok)
{
    if (tok != NULL)
        free(tok);
}