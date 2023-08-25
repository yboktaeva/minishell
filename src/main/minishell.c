/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:23 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/25 19:42:32 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int shell_loop(char *line, t_table *info)
{
    (void)info;
    int i;
    t_token *tokens;
    //t_node  *cmd_node = NULL;
    
    i = 0;
    int j = 0;
    tokens = malloc(sizeof(t_token *));
    if (!line)
    {
        ft_putendl_fd("exit", 1); //signal handker for ctrl + D
        free(line);
        return (0);
    }
    else
    {
        add_history(line);
        //remove_empty_quotes(line, &i, &j);
        //buf = add_space(line, "&/|/>/</<</>>/&&/||");
        j = split_tokens(line, tokens);
        //info->cmds = ft_split_quotes(buf, ' ');
        // while (info->cmds[i])
        //     printf("%s\n", info->cmds[i++]);
        while (i < j)
        {
            printf("Token %d: Type = %d, Value = %s\n", i, tokens[i].type, tokens[i].value);
            i++;
        }
        //cmd_node = generate_tree(line, tokens);
        //print_env(info->env);
        // printf("LEVEL %d: COMMAND: ", level);
        // for (int i = 0; cmd_node->cmd_args[i] != NULL; i++)
        // printf("%s ", cmd_node->cmd_args[i]);
        // // printf("INPUT: %s\n", root->input->file_name);
        // // printf("OUTPUT: %s\n", root->output->file_name);
        // // printf("HEREDOC: %s\n", root->input->file_name);
        // // printf("APPEND: %s\n", root->output->file_name);
        // printf("\n");
        // if (cmd_node->pipe_node != NULL)
        //     print_parse_tree(cmd_node->pipe_node, level + 1);
    }
    return (0);
}

int main(int ac, char **argv, char **envp)
{
    char *prompt;
    t_table info;
    
    if (ac > 2 || argv[1] != NULL)
    {
        ft_putendl_fd("Program does not accept any arguments", 1);
        exit (EXIT_FAILURE);
    }
    while (1)
    {
        prompt = readline("minishell$> ");
        init_main_table(&info, argv, envp);
        shell_loop(prompt, &info);
        free(prompt);
    }
   // free(prompt);
    free_all(prompt, &info, info.cmd_node);
    free_env(&info.env);
    return (EXIT_SUCCESS);
}