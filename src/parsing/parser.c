/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:41:33 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/28 13:45:15 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_syntax_errors(t_token *tokens, int *j);
//int get_tokens_size(char *line, t_token *tokens);

int parser(t_token *tokens, int n_tokens)
{
    int j;

    j = 0;
    while (j < n_tokens)
    {
        if (check_syntax_errors(tokens, &j) != 0)
        {
            syntax_error(tokens[j].value);
            return (-1);
        }
    }
    return(0);
}

int check_syntax_errors(t_token *tokens, int *j)
{
    if (tokens[0].type == PIPE || tokens[*j].value == NULL || (tokens[*j].type == PIPE && tokens[*j + 1].type != WORD))
        return (-1);
    else if ((tokens[*j].type == REDIR_IN && tokens[*j - 1].type == HEREDOC) ||
        (tokens[*j].type == REDIR_OUT && tokens[*j - 1].type == APPEND))
        return (-1);
    else if ((tokens[*j].type == HEREDOC && tokens[*j + 1].type == HEREDOC) ||
        (tokens[*j].type == APPEND && tokens[*j + 1].type == APPEND))
        return (-1);
    //else if ()
    (*j)++;
    return (0);
}

// int get_tokens_size(char *line, t_token *tokens)
// {
//     int count;

//     count = split_tokens(line, tokens);
//     return (count);
// }
