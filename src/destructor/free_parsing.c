/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:23:38 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/08/31 19:43:03 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void    free_one_cmd_list(t_one_cmd *head);
void    free_redirect_list(t_redir *head);
void    free_token(t_token *tokens, int n_tokens);

void    free_parse_list(t_parse_list *head)
{
    t_parse_list    *tmp;
    
    tmp = head;
    while (head)
    {
        tmp = head->next;
        if (head->one_cmd)
            free_one_cmd_list(head->one_cmd);
        if (head->input)
            free_redirect_list(head->input);
        if (head->output)
            free_redirect_list(head->output);
        free(head);
        head = tmp;
    }
}

// void    free_all(char *line, t_token *tokens, int n_tokens)
// {
//     if (line != NULL)
//     {
//         free(line);
//         line = NULL;
//     }
//     if (tokens != NULL)
//         free_token(tokens, n_tokens);
// }

void    free_token(t_token *tokens, int n_tokens)
{
    int i;

    i = 0;
    while (tokens && i < n_tokens)
    {
        free(tokens[i].value);
        i++;
    }
    free(tokens);
    return ;
}

void    free_one_cmd_list(t_one_cmd *head)
{
    t_one_cmd   *tmp;

    while (head)
    {
        tmp = head->next;
        free(head);
        head = tmp;
        tmp = NULL;
    }
}

void    free_redirect_list(t_redir *head)
{
    t_redir *tmp;

    while (head)
    {
        tmp = head->next;
        free(head);
        head = tmp;
        tmp = NULL;
    }
}