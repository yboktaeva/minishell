/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:23 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/21 00:10:55 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

char    *ft_readline(char *prompt)
{
    char    *line;
    
    line = (char *)malloc(sizeof(char) * (ft_strlen(prompt) + 1));
    if (!line)
        return (NULL);
    line = readline(prompt);
    if (!line)
    {
        ft_putendl_fd("exit", 1);
        free(line);
        return(NULL);
    }
    else
    {
        add_history(line);
        if (check_up(line) < 0)
        {
            free(line);
            return (NULL);
        }
    }
    return (line);
}

int shell_loop(char *line, t_table *info)
{
    int    i;
    t_token *tokens;
    //char    *buf;
    i = 0;
    tokens = NULL;
    if (line)
    {
        remove_empty_quotes(line);
        //buf = add_space(line, "&/|/>/</<</>>/&&/||");
        split_tokens(line, info->tokens);
        //info->cmds = ft_split_quotes(buf, ' ');
        // while (info->cmds[i])
        //     printf("%s\n", info->cmds[i++]);
        while (info->tokens[i].value != NULL)
        {
            printf("Token %d: Type = %d, Value = %s\n", i, info->tokens[i].type, info->tokens[i].value);
            i++;
        }
    }
    return (0);
}

int main(int ac, char **av, char **envp)
{
    (void)envp;
    char *prompt;
    t_table info;
    
    if (ac > 2 || av[1] != NULL)
    {
        ft_putendl_fd("Program does not accept any arguments", 1);
        exit (EXIT_FAILURE);
    }
    while (1)
    {
        prompt = ft_readline("minishell$> ");
        shell_loop(prompt, &info);
    }
    free(prompt);
    free_token(&info);
    return (EXIT_SUCCESS);
}