/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:53:58 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/28 15:06:36 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char	*env_var_name(char *str)
{
	char	*var_name;

	var_name = ft_substr(str, 0, env_var_name_len(str));
	if (var_name == NULL)
		return (NULL);
	return (var_name);
}

int	env_var_name_len(char *var_name)
{
	int	i;

	i = 0;
	if (*var_name == '?' || ft_isdigit(*var_name))
		return (1);
	while (var_name[i] == '_' || ft_isalpha(var_name[i])
		|| ft_isdigit(var_name[i]))
		i++;
	return (i);
}

char	*env_var_value(t_env *env, char *var_name)
{
	t_env	*head;
	int		var_name_len;

	if (!env)
		return (NULL);
	var_name_len = ft_strlen(var_name);
	head = env->next;
	while (head)
	{
		if (var_name[0] == '?')
			return (ft_itoa(g_status));
		else if (ft_strncmp(var_name, head->var_name, var_name_len + 1) == 0)
		{
			if (head->var_value == NULL)
				return (ft_strdup("\0"));
			return (ft_strdup(head->var_value));
		}
		head = head->next;
	}
	return (ft_strdup("\0"));
}

t_env	*get_last(t_env *env)
{
	t_env	*head;

	if (!env)
		return (NULL);
	head = env;
	while (head->next != NULL)
		head = head->next;
	return (head);
}
