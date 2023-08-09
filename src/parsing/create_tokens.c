/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:59:20 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/09 20:11:48 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void    free_token(t_token *tok)
{
    free(tok);
}
t_type identify_token_type(const char *line)
{
    if (ft_strcmp(line, "<") == 0)
        return (LESS);
    else if (ft_strcmp(line, "<<") == 0)
        return (LESSLESS);
    else if (ft_strcmp(line, ">") == 0)
        return (GREAT);
    else if (ft_strcmp(line, ">>") == 0)
        return (GREATGREAT);
    else if (ft_strcmp(line, "|") == 0)
        return (PIPE);
    else if (ft_strcmp(line, "'") == 0)
        return (S_QUOT);
    else if (ft_strcmp(line, "\"") == 0)
        return (D_QUOT);
    else if (ft_strcmp(line, "-") == 0)
        return (OPTION);
    else
        return (WORD);
}


void tokenize_cmd(char *line, t_table *info)
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
            info->tok[count].value = &line[i];
            info->tok[count].type = identify_token_type(&line[i]);
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