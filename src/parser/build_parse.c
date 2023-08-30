/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:10:29 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/30 17:47:58 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_parse_list    *parsing_tokens(t_token *tokens, int n_tokens)
{
    int is_correct;
    t_parse_list    *parse_list;
    
    parse_list = NULL;
    if (!tokens)
        return (NULL);
    parse_list = init_parse_list();
    is_correct = fill_parse_list(parse_list, tokens, n_tokens);
    {
        if (is_correct == -1)
        {
            free_parse_list(parse_list);
            //free_token(tokens, n_tokens);
            return (NULL);
        }
    }
    return (parse_list);
}

int fill_parse_list(t_parse_list *parse_list, t_token *tokens, int n_tokens)
{
    int i;

    i = 0;
    while (i < n_tokens)
    {
        if (is_word(tokens[i].type))
            if_word_token(tokens, parse_list, &i);
        else if (is_redir(tokens[i].type))
        {
            if (if_redir_token(tokens, parse_list, &i) == NULL)
                return (-1);
            i++;
        }
        else
        {
            if (if_pipe_token(tokens, parse_list, &i) == NULL)
                return (-1);
            parse_list = parse_list->next;
        }
        i++;
    }
    return (1);
}

// void    print_parse_list(t_parse_list *head)
// {
//     t_parse_list *curr;

//     curr = head->next;
//     while (curr)
//     {
//         printf("%s  ")
//     }
// }