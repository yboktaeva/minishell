/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:01:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/20 19:31:17 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

static char    **convert_parse_list(t_one_cmd *head);

void create_args(t_parse_list *parse_list, t_arg *arg)
{
    t_parse_list *head;

    head = parse_list;
    while (head)
    {
        arg->argv = convert_parse_list(head->one_cmd);
        arg->n_args = num_args(head->one_cmd);
        head = head->next;
    }
}

static char    **convert_parse_list(t_one_cmd *head)
{
    int i;
    int size;
    char    **arr;
    t_one_cmd *curr_cmd;
    
    size = num_args(head);
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