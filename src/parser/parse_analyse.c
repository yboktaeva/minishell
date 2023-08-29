/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_analyse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:52:40 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/29 16:52:43 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int check_syntax_errors(t_token *tokens, int *j);

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
