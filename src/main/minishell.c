/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:23 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/07 11:56:06 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void is_null(char *line, t_token *tokens, t_parse_list *parse_list, t_table *info)
{
    free_token(tokens, info->n_tokens);
    free_parse_list(parse_list);
    add_history(line);
    return ;
}

void shell_loop(t_env *env, char *line, t_table *info)
{
    t_token         *tokens;
    t_parse_list    *parse_list;
    
    tokens = NULL;
    parse_list = NULL;
    if (!line)
    {
        ft_putendl_fd("exit", 1); //signal ctrl + D
        free(line);
        return ;
    }
    else
    {
        tokens = tokenize_input(env, line, info);
        if (tokens == NULL)
            is_null(line, tokens, parse_list, info);
        else
        {
            //print_tokens(tokens, info->n_tokens);
            parse_list = parsing_tokens(tokens, info->n_tokens);
            //print_parse_list(parse_list);
        }
        if (parse_list == NULL)
            is_null(line, tokens, parse_list, info);
        else
        {
            /*execution part*/
            cmd_execution(parse_list, env);
            add_history(line);
            free_all(line, tokens, info->n_tokens, parse_list);
        }
    }
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
        shell_loop(env, prompt, &info);
    }
    free_env(&env);
    return (EXIT_SUCCESS);
}