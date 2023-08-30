/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_analyse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:52:40 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/30 18:26:29 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    if_word_token(t_token *tokens, t_parse_list *parse_list, int *j)
{
    t_one_cmd   *one_cmd;

    one_cmd = init_one_cmd(tokens[*j].value);
    one_cmd_node(&parse_list->one_cmd, one_cmd);
}

void    *if_redir_token(t_token *tokens, t_parse_list *parse_list, int *j)
{
    t_redir *node;
    
    if (!tokens[*j + 1].value || tokens[*j + 1].type != WORD)
        return (syntax_error(tokens[*j].value));
    else if ((tokens[*j].type == REDIR_IN && tokens[*j - 1].type == HEREDOC) ||
        (tokens[*j].type == REDIR_OUT && tokens[*j - 1].type == APPEND))
        return (syntax_error(tokens[*j].value));
    else if ((tokens[*j].type == HEREDOC && tokens[*j + 1].type == HEREDOC) ||
        (tokens[*j].type == APPEND && tokens[*j + 1].type == APPEND))
        return (syntax_error(tokens[*j].value));
    node = init_redir_list(tokens[*j].type, tokens[*j].value);
    if (tokens[*j].type == REDIR_IN || tokens[*j].type == HEREDOC)
        redir_node(&parse_list->input, node);
    else
        redir_node(&parse_list->output, node);
    (*j)++;
    return (node);
}

void    *if_pipe_token(t_token *tokens, t_parse_list *parse_list, int *j)
{
    t_parse_list    *node;
    if (tokens[0].type == PIPE || !tokens[(*j)++].value ||
        (tokens[*j].type == PIPE && tokens[*j + 1].type != WORD))
        return (syntax_error(tokens[*j].value));
    node = init_parse_list();
    add_node(parse_list, node);
    (*j)++;
    return (node);
}
