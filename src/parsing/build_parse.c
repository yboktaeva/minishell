/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:10:29 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/12 15:26:06 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void    init_data()
{
    
}
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
    info->count = 0;
    return (p_node);
}

t_node  *build_tree(t_table *info)
{
    t_node  *left;
    t_node  *right;
    
    left = create_node(info);
    while (info->tok[info->count]. type == PIPE)
    {
        info->count++;
        right = create_node(info);
        left->pipe_node = right;
        left = right;
    }
    if (info->tok[info->count].type == INPUT)
    {
        info->count++;
        left->input_redirect = info->tok[info->count].value;
        info->count++;
    }
    if (info->tok[info->count].type == OUTPUT ||
        info->tok[info->count].type == APPEND)
    {
        info->count++;
        left->output_redirect = info->tok[info->count].value;
        info->count++;
    }
    return (left);
}

// void print_parse_tree(t_node *p_node, int level)
// {
//     t_table info;
//     if (p_node == NULL)
//         return ;
//     t_node *root = parse_helper(&info);
//     printf("Level %d: Commande: %s\n", level, p_node->cmd);
//     print_parse_tree(p_node->pipe_node, level + 1);
// }