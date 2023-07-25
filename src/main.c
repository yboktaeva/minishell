/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:47:13 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/25 18:00:07 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av, char **envp)
{
    (void)av;
    (void)envp;
    
    char *prompt;

    if (ac != 1)
    {
        ft_putendl_fd("Program does not accept any arguments", 1);
        exit (0);
    }
    while (1)
        prompt = readline("minishell$");
    return (0);
}