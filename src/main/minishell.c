/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:23 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/24 01:19:49 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"
#include "utils.h"
#include "builtin.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int g_status;

static void is_null(char *line, t_token *tokens, t_parse_list *parse_list, t_table *info)
{
    free_all(tokens, info->n_tokens, parse_list);
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
        ft_putendl_fd("exit", 1);
        free_all(tokens, info->n_tokens, parse_list);
        free_fake_envp(info->arg);
        exit (g_status);
    }
    else if (line[0] != 0)
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
            cmd_execution(parse_list, info, env, info->arg);
            add_history(line);
            free_all(tokens, info->n_tokens, parse_list);
        }
    }
}

int main(int ac, char **argv, char **envp)
{
    char *prompt;
    t_table info;
    t_env   *env;
    t_arg arg;

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
        
        init_execve_args(&arg, env);
        init_main_table(&info, prompt, envp);
        info.env = env;
        info.arg = &arg;
        shell_loop(env, prompt, &info);
    }
    safe_exit(&info);
    free_env(&env);
    free_cmd_args(&arg);
    exit(g_status);
}