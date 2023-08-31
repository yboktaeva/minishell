/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:20:47 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/31 17:28:53 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     is_redir(t_type type)
{
    if (type == REDIR_IN || type == HEREDOC
        || type == REDIR_OUT || type == APPEND)
        return (1);
    return (0);
}

t_type     type_of_redir(t_type type)
{
    if (type == REDIR_IN || type == HEREDOC
        || type == REDIR_OUT || type == APPEND)
        return (type);
    return (0);
}

int     is_word(t_type type)
{
    if (type == WORD)
        return (1);
    return (0);
}

int     is_pipe(t_type type)
{
    if (type == PIPE)
        return (1);
    return (0);
}
