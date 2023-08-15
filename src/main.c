/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:47:13 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/15 19:17:30 by yuboktae         ###   ########.fr       */
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
    if (check_quotes(line) < 0)
    {
        quote_error();
        return (-1);
    }
    if (check_input(line) < 0)
    {
        syntax_error();
        return (-1);
    }
    return (0);
}

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
        return(NULL) ;
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

int ft_init(char *line, t_table *info)
{
    size_t     i;
    //char    *buf;
    i = 0;
    if (line)
    {
        remove_empty_quotes(line);
        //buf = add_space(line, "&/|/>/</<</>>/&&/||");
        tokenize_input(line, info);
        //info->cmds = ft_split_quotes(buf, ' ');
        // while (info->cmds[i])
        //     printf("%s\n", info->cmds[i++]);
        while (info->tok[i].value != NULL)
        {
            printf("Count %d: Token %zu: Type = %d, Value = %s\n", info->count, i, info->tok[i].type, info->tok[i].value);
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
        prompt = ft_readline("minishell$> ");
        ft_init(prompt, &info);
    }
    free(prompt);
    free_token(info.tok);
    return (EXIT_SUCCESS);
}