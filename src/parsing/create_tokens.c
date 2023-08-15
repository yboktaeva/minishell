/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:59:20 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/15 19:10:38 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

t_type identify_token_type(char *line)
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
    else if (ft_isspace(*line))
        return (DELIMETER);
    else if (*line == '\'')
        return (FIELD);
    else if (*line == '\"')
        return (EXP_FIELD);
    else
        return (WORD);
}

void tokenize_input(char *line, t_table *info)
{
    int     i;
    int     count;
    char    quote;

    i = 0;
    count = 0;
    info->tok = malloc(sizeof(t_token) * (ft_strlen(line) + 1));
    if (!info->tok)
        exit(EXIT_FAILURE);
    while (line[i])
    {
        info->tok[count].value = &line[i];
        info->tok[count].type = identify_token_type(&line[i]);
        count++;
        if (info->tok[count].type == FIELD || info->tok[count].type == EXP_FIELD)
        {
            quote = line[i];
            i++;
            while (line[i] && line[i] != quote)
            {
                //if (!ft_isspace(line[i]))
                {
                    info->tok[count].value = &line[i];
                    info->tok[count].type = WORD; 
                    count++;
                }
                i++;
            }
            if (line[i] == quote)
            {
                info->tok[count].value = &line[i];
                if (line[i] == '\'')
                    info->tok[count].type = FIELD;
                else if (line[i] == '\"')
                    info->tok[count].type = EXP_FIELD;
                count++;
            }
        }
        else if (info->tok[count].type == DELIMETER)
        {
            info->tok[count].value = &line[i];
            count++;
        } 
        line[i++] = '\0';
        i++;
    }
    info->tok[count].value = NULL;
}


// void tokenize_input(char *line, t_table *info)
// {
//     int     i;
//     int     len;
//     int     count;
//     char    quote;
    
//     i = 0;
//     count = 0;
//     quote = '\0';
//     len = ft_strlen(line);
//     info->tok = malloc(sizeof(t_token) * (len + 1));
//     if (!info->tok)
//         exit (EXIT_FAILURE);
//     while (line[i])
//     {
//         info->tok[count].type = identify_token_type(&line[i]);
//         info->tok[count].value = &line[i];
//         count++;
//         if (ft_isspace(line[i]))
//             line[i++] = '\0';
//         else
//         {
//             while (line[i] && !ft_isspace(line[i]))
//                 i++;
//             if (line[i])
//                 line[i++] = '\0';
//         }
//     }
//     info->tok[count].value = NULL;
// }

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

// < infile 'cat' '| ls' << EOF
// Token 0: Type = 5, Value = <
// Token 1: Type = 1, Value =  
// Token 2: Type = 0, Value = infile
// Token 3: Type = 1, Value =  
// Token 4: Type = 2, Value = '
// Token 5: Type = 0, Value = cat
// Token 6: Type = 2, Value = '
// Token 7: Type = 1, Value =  
// Token 8: Type = 2, Value = '
// Token 9: Type = 4, Value = |
// Token 10: Type = 1, Value =  
// Token 11: Type = 0, Value = ls
// Token 12: Type = 2, Value = '
// Token 13: Type = 1, Value =  
// Token 14: Type = 7, Value = <<
// Token 15: Type = 1, Value =  
// Token 16: Type = 0, Value = EOF

