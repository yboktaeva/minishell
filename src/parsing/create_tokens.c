/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:59:20 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/10 16:42:37 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

t_type identify_token_type(const char *line)
{
     if (*line == '<')
    {
        if (*(line + 1) == '<')
        return (HEREDOC);
        else
           return (INPUT);
    }
    else if (*line == '>')
    {
        if (*(line + 1) == '>')
        return (APPEND);
        else
            return (OUTPUT);
    }
    else if (*line == '|')
        return (PIPE);
    else
        return (WORD);
}

void tokenize_input(char *line, t_table *info)
{
    int i;
    int len;
    int count;
    int start_token;
    char    quote;
    
    i = 0;
    count = 0;
    quote = '\0';
    start_token = 0;
    len = ft_strlen(line);
    info->tok = malloc(sizeof(t_token) * (len + 1));
    if (!info->tok)
        exit (EXIT_FAILURE);
    while (line[i])
    {
        while (ft_isspace(line[i]) && quote == '\0')
            i++;
        if (line[i])
        {
            info->tok[count].value = (char *)&line[i];
            info->tok[count].type = identify_token_type(&line[i]);
            count++;
            while (line[i])
            {
                if (line[i] == quote)
                    quote = '\0';
                else if ((line[i] == '\'' || line[i] == '\"') && quote == '\0')
                    quote = line[i];
                else if (ft_isspace(line[i]) && quote == '\0')
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

void    free_token(t_token *tok)
{
    free(tok);
}