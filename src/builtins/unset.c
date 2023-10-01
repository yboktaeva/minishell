/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:58:28 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/01 14:34:24 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "utils.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	unset_variable(char *name, t_env *env);
static int	is_valid_name(char *name);
static void	error_message(char *name);

int	cmd_unset(t_one_cmd *one_cmd, t_env *env)
{
	while (one_cmd)
	{
		unset_variable(one_cmd->str, env);
		one_cmd = one_cmd->next;
	}
	return (0);
}

static int	unset_variable(char *name, t_env *env)
{
	t_env	*head;
	t_env	*prev_node;

	head = env;
	prev_node = NULL;
	if (!is_valid_name(name))
		return (1);
	while (head)
	{
		if (str_check(name, head->var_name))
		{
			if (prev_node)
				prev_node->next = head->next;
			else
				head = head->next;
			free_env_node(head);
			return (0);
		}
		prev_node = head;
		head = head->next;
	}
	return (0);
}

static int	is_valid_name(char *name)
{
	if (ft_strchr(name, '='))
	{
		error_message(name);
		return (0);
	}
	return (1);
}

static void	error_message(char *name)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
}
