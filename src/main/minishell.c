/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:23 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/27 20:04:43 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"
#include "utils.h"
#include "builtin.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int  g_status;

static void is_null(char *line, t_table *main)
{
    add_history(line);
    free_all(main, main->n_tokens);
    return ;
}

void shell_loop(t_env *env, char *line, t_table *main)
{
    t_token         *tokens;
    t_parse_list    *parse_list;
    
    tokens = NULL;
    parse_list = NULL;
    if (!line)
    {
        ft_putendl_fd("exit", STDOUT_FILENO);
        exit (g_status);
    }
    else if (line[0] != 0)
    {
        tokens = tokenize_input(env, line, main);
        if (tokens == NULL)
            is_null(line, main);
        else
        {
            //print_tokens(tokens, main->n_tokens);
            parse_list = parsing_tokens(tokens, main->n_tokens);
            //print_parse_list(parse_list);
        }
        if (parse_list == NULL)
            is_null(line, main);
        else
        {
            cmd_execution(parse_list, main);
            add_history(line);
            free_loop(main);
        }
    }
}

int main(int ac, char **argv, char **envp)
{
    char *prompt;
    t_table main;
    t_env   *env;
    t_arg   arg;

    if (ac > 2 || argv[1] != NULL)
    {
        ft_putendl_fd("Program does not accept any arguments", 1);
        exit (EXIT_FAILURE);
    }
    g_status = 0;
    env = init_env_list(envp);
    prompt = NULL;
    handle_sig(SIG_DEFAULT);
    while (1)
    {
        free(prompt);
        prompt = readline("minishell$> ");
        init_main_table(&main);
        main.env = env;
        init_execve_args(&arg, env);
        main.arg = &arg;
        shell_loop(env, prompt, &main);
    }
    safe_exit(&main);
    exit(g_status);
}