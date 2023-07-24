/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:09:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/24 15:59:47 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum s_type
{
    WORD,
    REDIRECT,
    PIPE
}   t_type;

typedef struct s_token
{
    t_type  type;
    char    *value;
}   t_token;

typedef struct s_info
{
    char    **cmd;
    char    *cmd_path;
    
}   t_info;
#endif