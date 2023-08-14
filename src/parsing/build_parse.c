/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:10:29 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/14 18:26:42 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

// void	init_data(void)
// {
// }
t_node	*create_node(t_table *info)
{
	t_node	*cmd_node;

	cmd_node = malloc(sizeof(struct s_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->cmd = info->tok[info->count].value;
	cmd_node->args = NULL;
	cmd_node->redirect_in_node = NULL;
	cmd_node->redirect_out_node = NULL;
    cmd_node->heredoc_node = NULL;
	cmd_node->pipe_node = NULL;
	info->count = 0;
	return (cmd_node);
}

// t_node	*build_tree(t_table *info)
// {
// 	t_node	*left;
// 	t_node	*right;

// 	left = create_node(info);
// 	while (info->tok[info->count].type == PIPE)
// 	{
// 		info->count++;
// 		right = create_node(info);
// 		left->pipe_node = right;
// 		left = right;
// 	}
// 	if (info->tok[info->count].type == REDIR_IN)
// 	{
// 		info->count++;
// 		left->redirect_in_node = info->tok[info->count].value;
// 		info->count++;
// 	}
// 	if (info->tok[info->count].type == REDIR_OUT
// 		|| info->tok[info->count].type == APPEND)
// 	{
// 		info->count++;
// 		left->redirect_out_node = info->tok[info->count].value;
// 		info->count++;
// 	}
// 	return (left);
// }

void    free_node(t_node *cmd_node)
{
    if (cmd_node == NULL)
        return ;
    //free all data in the node before free node
    //free(cmd_node->cmd);
    //free(cmd_node->args);
    //free(cmd_node->redirect_in_node);
    //free(cmd_node->redirect_out_node);
    //free(cmd_node->heredoc_node);
    free(cmd_node);
}
// void print_parse_tree(t_node *cmd_node, int level)
// {
//     t_table info;
//     if (cmd_node == NULL)
//         return ;
//     t_node *root = parse_helper(&info);
//     printf("Level %d: Commande: %s\n", level, cmd_node->cmd);
//     print_parse_tree(cmd_node->pipe_node, level + 1);
// }