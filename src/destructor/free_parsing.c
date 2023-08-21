/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:23:38 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/08/21 18:01:56 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void    free_token(t_token *tokens, int n_tokens);
void    free_parse_tree(t_node *cmd_node);

void    free_all(char *line, t_table *info, t_node *cmd_node)
{
    if (line != NULL)
    {
        free(line);
        //line = NULL;
    }
    if (info->tokens != NULL)
        free_token(info->tokens, info->n_tokens);
    if (cmd_node != NULL)
        free_parse_tree(cmd_node);
}

void    free_token(t_token *tokens, int n_tokens)
{
    int i;

    i = 0;
    while (i < n_tokens)
    {
        free(tokens[i].value);
        i++;
    }
    free(tokens);
    return ;
}

void    free_parse_tree(t_node *cmd_node)
{
    int i;

    i = 0;
    while (cmd_node->cmd_args[i] != NULL)
    {
        free(cmd_node->cmd_args[i]);
        i++;
    }
    if (cmd_node->input != NULL)
        free(cmd_node->input);
    if (cmd_node->output != NULL)
        free(cmd_node->output);
    free(cmd_node->pipe_node);
    free(cmd_node); 
     return ;
}
