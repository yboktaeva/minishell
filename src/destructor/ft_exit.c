/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:07:49 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/27 10:05:05 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void    safe_exit(t_table *main)
{
    rl_clear_history();
    free_env(&main->env);
    free_fake_envp(main->arg);
    free_all(main->tokens, main->n_tokens, main->parse_list);
    free_cmd_args(main->arg);
    if (main->cmd_info->fd != NULL)
        free(main->cmd_info->fd);
}

void    free_cmd_args(t_arg *arg)
{
    int	i;

	i = 0;
	if (arg->argv != NULL && *(arg->argv) != NULL)
    {
        while (arg->argv[i] != NULL)
        {
            free(arg->argv[i]);
            i++;
        }
        free(arg->argv);
    }
    arg->argv = NULL;
}