/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:47:13 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/10 17:12:39 by yuboktae         ###   ########.fr       */
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

int ft_init(char *line, t_table *info)
{
    size_t     i;
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
        //remove_same_quotes(line);
        buf = add_space(line, "&/|/>/</<</>>/&&/||");
        tokenize_input(buf, info);
        //info->cmds = ft_split_quotes(buf, ' ');
        // while (info->cmds[i])
        //     printf("%s\n", info->cmds[i++]);
        while (info->tok[i].value != NULL)
        {
            printf("Token %zu: Type = %d, Value = %s\n", i, info->tok[i].type, info->tok[i].value);
            i++;
        }
        
    }
    return (0);
}

int main(int ac, char **av, char **envp)
{
    (void)av;
    (void)envp;
    char *prompt;
    t_table info;
    
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
        ft_init(prompt, &info);
    }
    free(prompt);
    free_token(info.tok);
    return (EXIT_SUCCESS);
}