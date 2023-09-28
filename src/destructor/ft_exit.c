/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:07:49 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/28 15:16:45 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

void	safe_exit(t_table *main)
{
	rl_clear_history();
	free_all(main, main->n_tokens);
	free_env(&main->env);
	free_fake_envp(main);
	//free_cmd_args(main);
}

void	free_loop(t_table *main)
{
	free_all(main, main->n_tokens);
}

void	free_cmd_args(t_table *main)
{
	int	i;

	i = 0;
	if (main->arg->argv == NULL)
		return ;
	else if (main->arg->argv != NULL && *(main->arg->argv) != NULL)
	{
		while (main->arg->argv[i] != NULL)
		{
			free(main->arg->argv[i]);
			i++;
		}
		free(main->arg->argv);
		main->arg->argv = NULL;
	}
}
