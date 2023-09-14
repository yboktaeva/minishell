/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:01:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/14 19:44:46 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

static char    **convert_parse_list(t_one_cmd *head);

void create_args(t_parse_list *parse_list, t_arg *arg)
{
    arg->argv = convert_parse_list(parse_list->one_cmd);
    arg->n_args = num_args(parse_list->one_cmd);
}

static char    **convert_parse_list(t_one_cmd *head)
{
    int i;
    int size;
    t_one_cmd *curr_cmd;
    char    **arr;
    
    size = num_args(head);
    printf("%d\n", size);
    curr_cmd = head;
    arr = malloc(sizeof(char *) * (size + 1));
    if (!arr)
	{
		perror("Malloc failure in create_args");
		return (NULL);
	}
    i = 0;
    while (i < size)
    {
        arr[i] = curr_cmd->str;
        i++;
        curr_cmd = curr_cmd->next;
    }
    arr[size] = NULL;
    return (arr);
}