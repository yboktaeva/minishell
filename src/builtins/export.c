/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:59:02 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/21 17:24:00 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "exec.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int		procces_cmd(t_one_cmd *one_cmd, t_env *env);
static void		add_env_var_if_find(t_env *env, char *name, char *value);
static t_env	*create_env_var(const char *name, const char *value);
static void		add_env_var(t_env *env, const char *name, const char *value);

int	cmd_export(t_one_cmd *one_cmd, t_env *env)
{
	int	exit_status;

	exit_status = 0;
	if (one_cmd->next == NULL)
		return (print_export(env));
	while (one_cmd)
	{
		exit_status = procces_cmd(one_cmd, env);
		one_cmd = one_cmd->next;
	}
	return (exit_status);
}

static int	procces_cmd(t_one_cmd *one_cmd, t_env *env)
{
	int		exit_status;
	char	*name;
	char	*value;

	exit_status = 0;
	if (!valid_id(one_cmd->str))
		exit_status = export_bad_id(one_cmd->str);
	else if (char_check(one_cmd->str, '='))
	{
		name = one_cmd->str;
		value = ft_strchr(name, '=');
		if (value)
		{
			*value = '\0';
			value++;
			add_env_var_if_find(env, name, value);
		}
		else
			exit_status = export_bad_id(one_cmd->str);
	}
	else
		find_exported(env, one_cmd->str);
	return (exit_status);
}

static void	add_env_var_if_find(t_env *env, char *name, char *value)
{
	add_env_var(env, name, value);
	find_exported(env, name);
}

static void	add_env_var(t_env *env, const char *name, const char *value)
{
	t_env	*new_var;
	t_env	*last;

	new_var = create_env_var(name, value);
	if (env == NULL)
		env = new_var;
	else
	{
		last = get_last(env);
		last->next = new_var;
		new_var->next = NULL;
	}
}

static t_env	*create_env_var(const char *name, const char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (new_var == NULL)
	{
		perror("Memory alloc error");
		exit(1);
	}
	new_var->var_name = ft_strdup(name);
	new_var->var_value = ft_strdup(value);
	new_var->exported = 1;
	new_var->next = NULL;
	return (new_var);
}
