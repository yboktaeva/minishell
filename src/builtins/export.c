/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:59:02 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/03 11:39:02 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"
#include "utils.h"
#include "exec.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int		procces_cmd(t_one_cmd *one_cmd, t_env *env);
static void		add_env_var_if_find(t_env *env, char *name, char *value);
static void		add_env_var(t_env **env, const char *name, const char *value);
static char		*get_value(const char *str);

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
	char	*name;
	char	*value;

	value = NULL;
	if (!valid_id(one_cmd->str))
		return (export_bad_id(one_cmd->str));
	else if (char_check(one_cmd->str, '='))
	{
		name = one_cmd->str;
		value = get_value(name);
		if (value)
			add_env_var_if_find(env, name, value);
		else
			return (export_bad_id(one_cmd->str));
	}
	else if (!char_check(one_cmd->str, '=') && ft_strcmp("export", one_cmd->str))
	{
		name = one_cmd->str;
		if (!value)
			add_env_var_if_find(env, name, value);
	}
	else
		find_exported(env, one_cmd->str);
	return (0);
}

static char	*get_value(const char *str)
{
	char	*value;
	
	value = ft_strchr(str, '=');
	if (value)
	{
		*value = '\0';
		value++;
	}
	return (value);
}

static void	add_env_var_if_find(t_env *env, char *name, char *value)
{
	add_env_var(&env, name, value);
	find_exported(env, name);
}

static void	add_env_var(t_env **env, const char *name, const char *value)
{
	t_env	*var;
	t_env	*new_var;
	t_env	*last;

	var = find_env_var(*env, name);
	if (var)
	{
		free(var->var_value);
		var->var_value = ft_strdup(value);
	}
	else
	{
		new_var = create_env_var(name, value);
		if (*env == NULL)
			*env = new_var;
		else
		{
			last = get_last(*env);
			last->next = new_var;
			new_var->next = NULL;
		}
	}
}