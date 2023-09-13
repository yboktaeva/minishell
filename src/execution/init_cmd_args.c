/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:01:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/13 23:05:21 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

void create_args(t_parse_list *parse_list, t_arg *arg)
{
    int i;
    
    i = 0;
    arg->n_args = num_args(parse_list->one_cmd);
    arg->argv = malloc(sizeof(char *) * (arg->n_args + 1));
    if (!arg->argv)
	{
		perror("Malloc failure in create_args");
		return ;
	}
    while (parse_list->one_cmd)
    {
        arg->argv[i] = parse_list->one_cmd->str;
        i++;
        parse_list->one_cmd = parse_list->one_cmd->next;
    }
    arg->argv[i] = NULL;
}