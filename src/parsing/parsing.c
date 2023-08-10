/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:28:15 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/10 17:15:19 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

t_node  *create_node(t_table *info)
{
    t_node *p_node;

    p_node = malloc(sizeof(struct s_node));
    if (!p_node)
        return (NULL);
    p_node->cmd = info->tok[info->count].value;
    p_node->suffix = NULL;
    p_node->input_redirect = NULL;
    p_node->output_redirect = NULL;
    p_node->pipe_node = NULL;
    info->count++;
    return (p_node);
}

t_node  *parse_helper(t_table *info)
{
    t_node *left;
    t_node  *right;
    
    left = create_node(info);
    while (info->tok[info->count]. type == PIPE)
    {
        info->count++;
        right = create_node(info);
        left->pipe_node = right;
        left = right;
    }
    return (left);
}
