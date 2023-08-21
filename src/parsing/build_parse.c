/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:10:29 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/21 19:51:29 by yuboktae         ###   ########.fr       */
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
    redir->file_name = file_name;
    return (redir);
}

t_node	*create_node(char **cmd_args, void *pipe_node, t_redir *input, t_redir *output)
{
	t_node	*cmd_node;

	cmd_node = malloc(sizeof(struct s_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->cmd_args = cmd_args;
	cmd_node->pipe_node = pipe_node;
	cmd_node->input = input;
	cmd_node->output = output;
	return (cmd_node);
}

t_node	*generate_tree(t_token *tokens)
{
	t_node	*ast;
	t_node	*curr;
    t_redir *redir;
    int     pipex_count;
    int     cmd_count;
    int     i;
    
    i = -1;
    ast = NULL;
    curr = NULL;
    pipex_count = -1;
	while (++i < 100)
	{
        if (tokens[i].type == PIPE)
        {
            curr = create_node(NULL, NULL, NULL, NULL);
            cmd_count = 0;
            if (ast == NULL)
                ast = curr;
            else
                ast->pipe_node = curr;
            pipex_count = i;
        }
        else if (tokens[i].type == REDIR_IN || tokens[i].type == REDIR_OUT || tokens[i].type == HEREDOC || tokens[i].type == APPEND)
        {
            redir = create_redir(tokens[i].type, tokens[i].value);
            if (curr != NULL)
            {
                if (tokens[i].type == REDIR_IN)
                    curr->input = redir;
                else if (tokens[i].type == REDIR_IN)
                    curr->output = redir;
                else if (tokens[i].type == HEREDOC)
                    curr->input = redir;
                else if (tokens[i].type == APPEND)
                    curr->output = redir;
            }
        }
        else
        {
            if (curr == NULL)
            {
                curr = create_node(NULL, NULL, NULL, NULL);
                ast = curr;
            }
            curr->cmd_args[cmd_count] = tokens[i].value;
            cmd_count++;
        }
	}
	if (curr != NULL)
        curr->cmd_args[cmd_count] = NULL;
	return (ast);
}

void print_parse_tree(t_node *cmd_node, int level)
{
    if (cmd_node == NULL)
        return ;
    printf("LEVEL %d: COMMAND: ", level);
    for (int i = 0; cmd_node->cmd_args[i] != NULL; i++)
        printf("%s ", cmd_node->cmd_args[i]);
    printf("\n");
    print_parse_tree(cmd_node->pipe_node, level + 1);
}