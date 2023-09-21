/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:50:19 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/21 15:25:43 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	free_env(t_env **head)
{
	t_env	*tmp;
	t_env	*stock;

	if (!(*head))
		return ;
	tmp = *head;
	stock = NULL;
	while (tmp != NULL)
	{
		stock = tmp->next;
		free(tmp->str);
		free(tmp->var_name);
		free(tmp->var_value);
		free(tmp);
		tmp = stock;
	}
	*head = NULL;
}

void	free_env_node(t_env *head)
{
	if (!head)
		return ;
	if (head->exported != 0)
	{
		free(head->var_name);
		free(head->var_value);
	}
	if (head->exported == -1)
		free(head->str);
	free(head);
}