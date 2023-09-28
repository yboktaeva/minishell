/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:07:49 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/28 21:39:34 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

void	safe_exit(t_table *main)
{
	rl_clear_history();
	free_env(&main->env);
	free_fake_envp(main);
}

void	free_cmd_args(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return ;
	else if (argv != NULL && *(argv) != NULL)
	{
		while (argv[i] != NULL)
		{
			free(argv[i]);
			i++;
		}
		free(argv);
		argv = NULL;
	}
}
