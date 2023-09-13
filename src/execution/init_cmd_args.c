/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:01:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/13 20:51:43 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

void create_args(t_one_cmd *one_cmd, t_arg *arg)
{
    int i;
    
    i = 0;
    arg->n_args = num_args(one_cmd);
    arg->argv = malloc(sizeof(char *) * (arg->n_args + 1));
    if (!arg->argv)
	{
		perror("Malloc failure in create_args");
		return ;
	}
    while (one_cmd)
    {
        arg->argv[i] = one_cmd->str;
        i++;
        one_cmd = one_cmd->next;
    }
    arg->argv[i] = NULL;
}

void    init_args(t_parse_list *parse_list, t_arg *arg)
{
    t_one_cmd   *cur_cmd;
    while (parse_list)
    {
        cur_cmd = parse_list->one_cmd;
        while (cur_cmd != NULL)
        {
            create_args(cur_cmd, arg);
            cur_cmd = cur_cmd->next; 
        }
        parse_list = parse_list->next;
    }
}