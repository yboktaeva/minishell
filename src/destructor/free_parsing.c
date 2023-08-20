/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:23:38 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/08/20 23:48:56 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void    free_token(t_table *info);
//void    free_parse_tree();

void    free_all(char *line, t_token *tokens, t_tree *parsing)
{
    if (line != NULL)
    {
        free(line);
        line = NULL;
    }
    if (tokens != NULL)
        free_token(token);
    if (parsing != NULL)
        free_parse_tree(parsing);
}

void    free_token(t_table *info)
{
    int i;

    i = 0;
    while (i < info->n_tokens)
    {
        free(info->tokens[n_tokens].value);
        i++;
    }
    free(info->tokens);
    return ;
}

// void    free_parse_tree()
// {
    
// }
