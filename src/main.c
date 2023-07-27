/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:47:13 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/27 15:01:12 by yuboktae         ###   ########.fr       */
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
    if (!check_quotes(line) || !check_double_quotes(line))
    {
        ft_putendl_fd("error: quotes are not valid", 2);
        free(line);
        return (FAULSE);
    }
    // if (check_input(*args))
    // {
    //     ft_putendl_fd("minishell: syntax error", 2);
    //     free(line);
    //     free(args);
    //     return (FAULSE);
    // }
    return (TRUE);
}

int ft_init(char **args, char *line)
{
    int i;

    i = 0;
    if (empty_line(line))
    {
        free(line);
        return (FAULSE);
    }
    if (line)
    {
        add_history(line);
        if (!check_up(line))
            return (FAULSE);
        while (line[i])
        {
            args = ft_split_quotes(line, ' ');
            i++;
        }
    }
    return (TRUE);   
}

int main(int ac, char **av, char **envp)
{
    (void)av;
    (void)envp;
    char *prompt;
    char **args;
    
    args = NULL;
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
        else
            ft_init(args, prompt);
    }
    free(prompt);
    return (EXIT_SUCCESS);
}