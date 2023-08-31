/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_analyse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:52:40 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/31 20:59:28 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    *syntax_redir(t_token *tokens, int *j, int end);
static void    *syntax_pipe(t_token *tokens, int *j, int end);

void    if_word_token(t_token *tokens, t_parse_list *parse_list, int *j)
{
    t_one_cmd   *one_cmd;

    one_cmd = init_one_cmd(tokens[*j].value);
    one_cmd_node(&parse_list->one_cmd, one_cmd);
}

void    *if_redir_token(t_token *tokens, t_parse_list *parse_list, int *j, int end)
{
    t_redir *node;
    
    if (syntax_redir(tokens, j, end) == NULL)
        return (NULL);
    node = init_redir_list(tokens[*j].type, tokens[*j].value);
    if (tokens[*j].type == REDIR_IN || tokens[*j].type == HEREDOC)
        redir_node(&parse_list->input, node);
    else
        redir_node(&parse_list->output, node);
    return (node);
}

void    *if_pipe_token(t_token *tokens, t_parse_list *parse_list, int *j, int end)
{
    t_parse_list    *node;
    
    if (syntax_pipe(tokens, j, end) == NULL)
        return (NULL);
    else
    {
        node = init_parse_list();
        add_node(parse_list, node);
    }
    return (node);
}

static void    *syntax_redir(t_token *tokens, int *j, int end)
{
    if (is_redir(tokens[end - 1].type)
        || (tokens[0].type == REDIR_IN && tokens[end - 1].type == REDIR_OUT))
        return (syntax_error("newline"));
    else if (tokens[*j + 1].type != WORD)
        return (syntax_error(tokens[*j].value));
    else if (tokens[*j].type == type_of_redir(tokens[*j].type))
        return (syntax_error(tokens[*j].value));
    return (SUCCES);
}

static void    *syntax_pipe(t_token *tokens, int *j, int end)
{
    if (tokens[0].type == PIPE || tokens[end - 1].type == PIPE)
        return (syntax_error(tokens[*j].value));
    return (SUCCES);
}

// static void *syntax_redir(t_token *tokens, int *j, int end) {
//     if (*j == 0 || *j == end - 1 || !is_word(tokens[*j + 1].type)) { // Assuming is_word() checks if a token is a word
//         return (syntax_error("newline"));
//     }
//     else if (is_redir(tokens[*j].type) && is_redir(tokens[*j + 1].type)) {
//         return (syntax_error(tokens[*j].value));
//     }
//     return (SUCCES);
// }
