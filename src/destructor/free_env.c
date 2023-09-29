/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:50:19 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/29 18:56:25 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	free_env(t_env **head)
{
	t_env	*tmp;
	t_env	*stock;

	if (head == NULL && *head == NULL)
		return ;
	tmp = *head;
	stock = NULL;
	while (tmp)
	{
		stock = tmp->next;
		free(tmp->var_name);
		free(tmp->var_value);
		free(tmp->str);
		free(tmp);
		tmp = stock;
	}
	*head = NULL;
}

void	free_env_node(t_env *head)
{
	if (head == NULL)
		return ;
	if (head->exported != 0)
	{
		if (head->var_name && head->var_value)
		{
			free(head->var_name);
			free(head->var_value);
		}
	}
	if (head->exported == -1)
		free(head->str);
	free(head);
	head = NULL;
}

void	free_fake_envp(t_table *main)
{
	int	i;

	i = 0;
	if (main->arg->envp != NULL && *(main->arg->envp) != NULL)
	{
		while (main->arg->envp[i] != NULL)
		{
			// free(main->arg->envp[i]);
			 i++;
		}
		free(main->arg->envp);
		main->arg->envp = NULL;
	}
	else
		return ;
}
