/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:23 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/02 19:07:17 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "builtin.h"
#include "exec.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int			g_status;

static void	is_null(char *line, t_table *main)
{
	add_history(line);
	free_all(main, main->n_tokens);
	return ;
}

static void	free_line(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	rl_clear_history();
	exit(g_status);
}

static void	error_msg(int ac, char **argv)
{
	if (ac > 2 || argv[1] != NULL)
	{
		ft_putendl_fd("Program does not accept any arguments", 1);
		exit(EXIT_FAILURE);
	}
}

void	shell_loop(t_env *env, char *line, t_table *main)
{
	if (!line)
	{
		free_env(&env);
		free_fake_envp(main);
		free_line();
	}
	else if (line[0] != 0)
	{
		main->tokens = tokenize_input(env, line, main);
		print_tokens(main->tokens, main->n_tokens);
		if (main->tokens == NULL)
			is_null(line, main);
		else
		{
			main->parse_list = parsing_tokens(main->tokens, main->n_tokens);
			//print_parse_list(main->parse_list);
		}
		if (main->parse_list == NULL)
			is_null(line, main);
		else
		{
			cmd_execution(main->parse_list, main);
			add_history(line);
			free_execution(main);
		}
	}
}

int	main(int ac, char **argv, char **envp)
{
	char	*prompt;
	t_table	main;
	t_env	*env;
	t_arg	arg;

	error_msg(ac, argv);
	g_status = 0;
	env = init_env_list(envp);
	prompt = NULL;
	handle_sig(SIG_DEFAULT);
	init_main_table(&main);
	main.env = env;
	init_execve_args(&arg, main.env);
	main.arg = &arg;
	while (1)
	{
		free(prompt);
		handle_sig(SIG_DEFAULT);
		prompt = readline("minishell$> ");
		shell_loop(main.env, prompt, &main);
	}
	safe_exit(&main);
	exit(g_status);
}
