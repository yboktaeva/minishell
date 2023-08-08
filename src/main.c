/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:47:13 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/08 20:05:47 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int  check_up(char *line)
{
    if (check_quotes(line) == -1)
    {
        ft_putendl_fd("error: quotes are not closed", 2);
        return (-1);
    }
    if (check_input(line) < 0)
    {
        ft_putendl_fd("minishell: syntax error", 2);
        return (-1);
    }
    return (0);
}

int ft_init(char **cmds, char *line)
{
    int     i;
    char    *buf;

    i = 0;
    if (line == NULL)
    {
        free(line);
        return (-1);
    }
    if (line)
    {
        add_history(line);
        if (check_up(line) < 0)
        {
            free(line);
            return (-1);
        }
        remove_same_quotes(line);
        //printf("%s\n", line++);
        buf = add_space(line, "&/|/>/</<</>>/&&/||");
        cmds = ft_split_quotes(buf, ' ');
        while (cmds[i])
            printf("%s\n", cmds[i++]);
    }
    return (0);   
}

int main(int ac, char **av, char **envp)
{
    (void)av;
    (void)envp;
    char *prompt;
    char **cmds;
    
    cmds = NULL;
    if (ac != 1 || av[1] != NULL)
    {
        ft_putendl_fd("Program does not accept any arguments", 1);
        exit (EXIT_SUCCESS);
    }
    while (1)
    {
        prompt = readline("minishell$> ");
        if (!prompt)
        {
            ft_putendl_fd("exit", 1);
            break ;
        }
        ft_init(cmds, prompt);
    }
    free(prompt);
    return (EXIT_SUCCESS);
}