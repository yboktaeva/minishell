/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:01:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/12 18:14:24 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

char    **create_args(t_parse_list *parse_list, int n_args)
{
    int i;
    char    **exec_argv;

    i = 0;
    n_args = num_args(parse_list->one_cmd);
    exec_argv = (char **)malloc(sizeof(char *) * (n_args + 2));
    if (!exec_argv)
	{
		perror("Malloc failure in create_args");
		return (NULL);
	}
    while (parse_list->one_cmd)
    {
        exec_argv[i] = parse_list->one_cmd->str;
        i++;
        parse_list->one_cmd = parse_list->one_cmd->next;
    }
    exec_argv[i] = NULL;
    return (exec_argv);
}