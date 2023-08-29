/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:10:29 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/28 13:45:33 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

t_redir *create_redir(t_type type, char *file_name)
{
    t_redir *redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->type = type;
    redir->file_name = ft_strdup(file_name);
    return (redir);
}

t_node	*create_node(char **cmd_args)
{
	t_node	*cmd_node;

	cmd_node = malloc(sizeof(struct s_node));
	if (!cmd_node)
		return (NULL);
    cmd_node->cmd_args = malloc(sizeof(char **));
    if (!cmd_node->cmd_args)
    {
        return (NULL);
    }
	cmd_node->cmd_args = cmd_args;
	cmd_node->pipe_node = NULL;
	cmd_node->input = NULL;
	cmd_node->output = NULL;
	return (cmd_node);
}

// t_node	*generate_tree(char *line, t_token *tokens)
// {
// 	t_node	*ast;
// 	t_node	*curr;
//     t_redir *redir;
//     int     pipe_count;
//     int     n_tokens;
//     int     cmd_count;
//     int     i;
    
//     i = 0;
//     ast = NULL;
//     curr = NULL;
//     cmd_count = 0;
//     pipe_count = -1;
//     //n_tokens = get_tokens_size(line, tokens);
//     // if (lexer(tokens, n_tokens) == -1)
//     // {
//     //     return (NULL);
//     // }
// 	while (i < n_tokens)
// 	{
//         if (tokens[i].type == PIPE)
//         {
//             curr = create_node(&tokens[i].value);
//             if (ast == NULL)
//                 ast = curr;
//             else
//                 ast->pipe_node = curr;
//             pipe_count = i;
//         }
//         else if (tokens[i].type == REDIR_IN || tokens[i].type == REDIR_OUT || tokens[i].type == HEREDOC || tokens[i].type == APPEND)
//         {
//             redir = create_redir(tokens[i].type, tokens[i].value);
//             if (curr != NULL)
//             {
//                 if (tokens[i].type == REDIR_IN)
//                     curr->input = redir;
//                 else if (tokens[i].type == REDIR_OUT)
//                     curr->output = redir;
//                 else if (tokens[i].type == HEREDOC)
//                     curr->input = redir;
//                 else if (tokens[i].type == APPEND)
//                     curr->output = redir;
//             }
//         }
//         else
//         {
//             if (curr == NULL)
//             {
//                 curr = create_node(&tokens[i].value);
//                 ast = curr;
//             }
//             curr->cmd_args[cmd_count] = ft_strdup(tokens[i].value);
//             cmd_count++;
//         }
//         i++;
// 	}
// 	if (curr != NULL)
//         curr->cmd_args[cmd_count] = NULL;
//     // printf("PIPE: %d\n", pipe_count);
    
// 	return (ast);
// }

// void print_parse_tree(t_node *root, int level)
// {
//     if (root != NULL)
//     {
//         printf("LEVEL %d: COMMAND: ", level);
//         for (int i = 0; root->cmd_args[i] != NULL; i++)
//         {
//             printf("%s ", root->cmd_args[i]);
//             // printf("INPUT: %s\n", root->input->file_name);
//             // printf("OUTPUT: %s\n", root->output->file_name);
//             // printf("HEREDOC: %s\n", root->input->file_name);
//             // printf("APPEND: %s\n", root->output->file_name);
//         }
//         printf("\n");
//         if (root->pipe_node != NULL)
//             print_parse_tree(root->pipe_node, level + 1);
//     }
// }