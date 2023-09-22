/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:07:49 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/22 16:49:17 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void    safe_exit(t_table *info)
{
    free_all(info->tokens, info->n_tokens, info->parse_list);
    free_fake_envp(info->arg);
}

void    free_cmd_args(t_arg *arg)
{
    int	i;

	i = 0;
	if (arg->argv != NULL)
    {
        while (arg->argv[i] != NULL)
        {
            free(arg->argv[i]);
            i++;
        }
        free(arg->argv);
    }
}