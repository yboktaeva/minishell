/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:23 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/21 19:50:08 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void    ft_readline(char *line)
{
    if (!line)
    {
        ft_putendl_fd("exit", 1);
        free(line);
        return ;
    }
    else
    {
        add_history(line);
        if (check_up(line) < 0)
        {
            //free(line);
            return ;
        }
    }
}

int shell_loop(char *line, t_table *info)
{
    int i;
    t_token *tokens;
    t_node  *cmd_node;
    //char    *buf;
    (void)info;
    
    i = 0;
    int j = 0;
    tokens = malloc(sizeof(t_token) * 100); // MULTIPLIER par find_array_size (split prompt " ")
    if (line)
    {
        //remove_empty_quotes(line);
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
        cmd_node = generate_tree(tokens);
        print_parse_tree(cmd_node, 0);
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
        ft_readline(prompt);
        init_main_table(&info, argv, envp);
        shell_loop(prompt, &info);
        //free(prompt);
    }
    free(prompt);
    free_all(prompt, &info, info.cmd_node);
    return (EXIT_SUCCESS);
}