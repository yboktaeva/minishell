/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:20:47 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/30 17:21:00 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     is_redir(t_type type)
{
    if (type == REDIR_IN || type == REDIR_OUT
        || type == HEREDOC || type == APPEND)
        return (1);
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
