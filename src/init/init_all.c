/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:57:27 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/08/29 20:00:00 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void init_main_table(t_table *info, char *line, char **argv)
{
    (void)argv;
    //t_token tokens;
    
    //info->cmds =;
   //info->path = get_executable_path(info->env);
    info->n_tokens = count_tokens(line);
    info->cmd_count = 0;
    info->cmd_node = NULL;
}