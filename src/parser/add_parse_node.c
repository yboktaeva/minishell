/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_parse_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:59:59 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/08 18:11:19 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

void	one_cmd_node(t_one_cmd **head, t_one_cmd *node)
{
	t_one_cmd	*end;

	if (*head == NULL)
		*head = node;
	else
	{
		end = *head;
		while (end->next)
			end = end->next;
		end->next = node;
	}
}

void	redir_node(t_redir **head, t_redir *node)
{
	t_redir	*end;

	if (*head == NULL)
		*head = node;
	else
	{
		end = *head;
		while (end->next)
			end = end->next;
		end->next = node;
	}
}

void	add_node(t_parse_list *parse_list, t_parse_list *node)
{
	parse_list->next = node;
}
