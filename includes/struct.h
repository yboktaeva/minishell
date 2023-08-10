/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:09:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/10 17:05:42 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum s_type
{
    WORD,
    PIPE,
    INPUT,
    OUTPUT,
    HEREDOC,
    APPEND
}   t_type;

typedef struct s_token
{
    t_type  type;
    char    *value;
}   t_token;

typedef struct s_node
{
    char    *cmd;
    char    **suffix;
    char    *input_redirect;
    char    *output_redirect;
    struct s_node   *pipe_node;
}   t_node;

typedef struct s_table
{
    char    **cmds;
    char    *cmd_path;
    t_token *tok;
    t_node  *p_node;
    int     count;
}   t_table;

#endif