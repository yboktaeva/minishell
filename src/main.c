/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:47:13 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/26 18:00:39 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int ac, char **av, char **envp)
{
    (void)av;
    (void)envp;
    
    char *prompt;

    if (ac != 1 || av[1] != NULL)
    {
        ft_putendl_fd("Program does not accept any arguments", 1);
        exit (EXIT_SUCCESS);
    }
    while (1)
    {
        prompt = readline("minishell$> ");
        if (prompt == NULL)
        {
            ft_putendl_fd("exit", 1);
            break ;
        }
        else
            lexer(prompt);
    }
    free(prompt);
    return (EXIT_SUCCESS);
}