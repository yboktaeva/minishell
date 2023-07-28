/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:09:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/28 17:30:00 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum s_type
{
    WORD,
    LESS,
    GREAT,
    LESSLESS,
    GREATGREAT,
    S_QUOT,
    D_QUOT,
    PIPE
}   t_type;

typedef struct s_token
{
    t_type  type;
    char    *value;
}   t_token;

typedef struct s_table
{
    char    **cmds;
    char    *cmd_path;
}   t_table;
#endif