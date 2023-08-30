/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:23 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/30 19:38:02 by yuboktae         ###   ########.fr       */
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
    add_history(line);
    free_all(line, tokens, info->n_tokens);
    free_parse_list(parse_list);
    return ;
}

void shell_loop(t_env *env, char *line, t_table *info)
{
    t_token *tokens;
    t_parse_list *parse_list;
    
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
        //print_env_list(env);
        tokens = tokenize_input(env, line);
        if (tokens == NULL)
            is_null(line, tokens, parse_list, info);
        else
            //print_tokens(tokens, info->n_tokens);
            parse_list = parsing_tokens(tokens, info->n_tokens);
        if (parse_list == NULL)
            is_null(line, tokens, parse_list, info);
        else
        {
            /*execution part*/
            //execute_cmd(parse_list, env);
            add_history(line);
            free_all(line, tokens, info->n_tokens);
            free_parse_list(parse_list);
            free_env(&env);
        }
    }
}

int main(int ac, char **argv, char **envp)
{
    char *prompt;
    t_table info;
    t_env   *env;
    int n_tokens;

    n_tokens = 0;
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
        //free(prompt);
    }
    return (EXIT_SUCCESS);
}