/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:07:49 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/01 17:58:43 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

void	safe_exit(t_table *main)
{
	rl_clear_history();
	free_env(&main->env);
	free_execution(main);
	free_n_close_heredoc(main->here_doc, 0);
}

void	free_execution(t_table *main)
{
	free_fake_envp(main);
	free_all(main, main->n_tokens);
	free_cmd_args(main->arg->argv);
}

void	free_cmd_args(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return ;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		argv[i] = NULL;
		i++;
	}
	free(argv);
	argv = NULL;
}
