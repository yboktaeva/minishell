/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:59:02 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/17 12:18:52 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static t_env *create_env_var(const char *name, const char *value);
static void add_env_var(t_env *env, const char *name, const char *value);
static int print_export(t_env *env);
static void find_exported(t_env *env, char *var_name);

int cmd_export(t_one_cmd *one_cmd, t_env *env)
{
    int exit_status;
    char *name;
    char *value;
    
	exit_status = 0;
    if (one_cmd->next == NULL)
		return (print_export(env));
    while (one_cmd)
    {
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
                add_env_var(env, name, value);
                find_exported(env, name);
            }
			else
				exit_status = export_bad_id(one_cmd->str);
        }
        else
			find_exported(env, one_cmd->str);
        one_cmd = one_cmd->next;
    }
    return (exit_status);
}

static void add_env_var(t_env *env, const char *name, const char *value)
{
	t_env *new_var;

    new_var = create_env_var(name, value);
    new_var->next = env->next;
    env->next = new_var;
}

static t_env *create_env_var(const char *name, const char *value)
{
	t_env *new_var;

    new_var = malloc(sizeof(t_env));
    if (new_var == NULL)
    {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    new_var->var_name = ft_strdup(name);
    new_var->var_value = ft_strdup(value);
    new_var->exported = 1;
    new_var->next = NULL;
    return (new_var);
}

static int print_export(t_env *env)
{
	t_env *tmp;

    tmp = env->next;
    while (tmp)
    {
        if (!tmp->exported)
            printf("declare -x %s=\"%s\"\n", tmp->var_name, tmp->var_value);
        tmp = tmp->next;
    }
    return (EXIT_SUCCESS);
}

static void find_exported(t_env *env, char *var_name)
{
    t_env *tmp;

    tmp = env->next;
    while (tmp)
    {
        if (ft_strcmp(var_name, tmp->var_name) == 0)
        {
            tmp->exported = 1;
            break;
        }
        tmp = tmp->next;
    }
}
