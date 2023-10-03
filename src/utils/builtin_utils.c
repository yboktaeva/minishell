/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:33:26 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/03 11:10:04 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "builtin.h"
#include "minishell.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	str_check(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (0);
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (0);
		str1++;
		str2++;
	}
	return (*str1 == '\0' && *str2 == '\0');
}

int	char_check(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i += 1;
	}
	return (0);
}

int	specific_path_home(t_env *env, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path(str, env);
	if (tmp == NULL)
	{
		return (-1);
	}
	ret = chdir(tmp);
	if (ret != 0)
	{
		chdir_error(tmp);
		return (ret);
	}
	change_path(env);
	return (ret);
}

t_env	*create_env_var(const char *name, const char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (new_var == NULL)
	{
		perror("export: malloc failed");
		exit(1);
	}
	new_var->var_name = ft_strdup(name);
	new_var->var_value = ft_strdup(value);
	new_var->exported = 1;
	new_var->next = NULL;
	return (new_var);
}