/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:53:58 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/11 20:08:10 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

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

char	*env_var_value(t_env *head, char *var_name)
{
	t_env	*env;
	int		var_name_len;

	env = head->next;
	var_name_len = ft_strlen(var_name);
	// if (*var_name == '?')
	// {
	//     return (ft_itoa(g_status));
	// }
	while (env)
	{
		if (ft_strncmp(var_name, env->var_name, var_name_len + 1) == 0)
		{
			if (env->var_value == NULL)
				return (ft_strdup(""));
			return (ft_strdup(env->var_value));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

// char    *find_env_value(t_env* env, char *var_name)
// {
//     while (env != NULL)
//     {
//         if (strcmp(env->var_name, var_name) == 0)
//             return env->var_value;
//         env = env->next;
//     }
//     return (NULL);
// }


// t_env   *get_last(t_env *env)
// {
//     if (!env)
//         return (NULL);
//     while (env->next != NULL)
//         env = env->next;
//     return (env);
// }