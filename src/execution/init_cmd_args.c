/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:01:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/14 15:45:43 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

void create_args(t_parse_list *parse_list, t_arg *arg)
{
    int i;
    t_one_cmd *curr_cmd;
    
    curr_cmd = parse_list->one_cmd;
    arg->n_args = num_args(curr_cmd);
    arg->argv = malloc(sizeof(char *) * (arg->n_args + 1));
    if (!arg->argv)
	{
		perror("Malloc failure in create_args");
		return ;
	}
    i = 0;
    while (curr_cmd)
    {
        arg->argv[i] = curr_cmd->str;
        i++;
        curr_cmd = curr_cmd->next;
    }
    arg->argv[i] = NULL;
}