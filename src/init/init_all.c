/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:57:27 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/08/22 17:47:51 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_main_table(t_table *info, char **argv, char **envp)
{
    (void)argv;
    //t_token tokens;
    
    info->env = get_env(envp);
    //info->cmds =;
   // info->path = get_executable_path();
    //info->tokens = NULL;
    //info->n_tokens = 0;
    info->cmd_count = 0;
    info->cmd_node = NULL;
}