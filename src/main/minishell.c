/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:23 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/29 20:00:26 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void *shell_loop(char *line, t_table *info)
{
    int i;
    
    i = 0;
    if (!line)
    {
        ft_putendl_fd("exit", 1); //signal ctrl + D
        free(line);
        return (NULL);
    }
    else
    {
        add_history(line);
        if (info->n_tokens < 1)
            return (NULL);
        info->tokens = malloc(sizeof(struct s_token) * info->n_tokens);
        if (!info->tokens)
            return (NULL);
        info->tokens = split_tokens(line, info->tokens);
        while (i < info->n_tokens)
        {
            printf("Token %d: Type = %d, Value = %s\n", i, info->tokens[i].type, info->tokens[i].value);
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
    return (NULL);
}

int main(int ac, char **argv, char **envp)
{
    char *prompt;
    t_table info;
    t_env   *env;
    
    if (ac > 2 || argv[1] != NULL)
    {
        ft_putendl_fd("Program does not accept any arguments", 1);
        exit (EXIT_FAILURE);
    }
    env = init_env_list(envp);
    while (1)
    {
        prompt = readline("minishell$> ");
        init_main_table(&info, prompt, argv);
        shell_loop(prompt, &info);
        free(prompt);
    }
   // free(prompt);
    free_all(prompt, &info, info.cmd_node);
    free_env(&info.env);
    return (EXIT_SUCCESS);
}