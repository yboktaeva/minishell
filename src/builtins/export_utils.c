/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:46:37 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/28 20:40:23 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env->next;
	while (tmp)
	{
		if (tmp->exported)
			printf("declare -x %s=\"%s\"\n", tmp->var_name, tmp->var_value);
		tmp = tmp->next;
	}
	return (0);
}

int	valid_id(char *str)
{
	size_t	i;

	i = 0;
	if (str_check(str, "="))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[i]) || str[i] == '!' || str[i] == '@'
			|| str[i] == '{' || str[i] == '}' || str[i] == '-')
			return (0);
		i += 1;
	}
	return (1);
}

int	export_bad_id(char *id)
{
	printf("minishell: export: `%s': not a valid identifier\n", id);
	return (EXIT_FAILURE);
}

void	find_exported(t_env *env, char *var_name)
{
	t_env	*tmp;

	tmp = env->next;
	while (tmp)
	{
		if (ft_strcmp(var_name, tmp->var_name) == 0)
		{
			tmp->exported = 1;
			break ;
		}
		tmp = tmp->next;
	}
}

t_env *find_env_var(t_env *env, const char *name)
{
	t_env *current;

    if (name == NULL || env == NULL)
        return (NULL);
    current = env->next;
    while (current)
    {
        if (current->var_name && ft_strcmp(current->var_name, name) == 0)
            return (current);
        current = current->next;
    }
    return (NULL);
}
