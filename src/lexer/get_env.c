/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:08:15 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/08 19:00:17 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

void	set_env_list(t_env **head, char **envp);
void	get_env(t_env *head, char *str);
t_env	*add_env_node(char *str);
t_env	*copy_env(t_env *env, char *str);

t_env	*init_env_list(char **envp)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var_name = NULL;
	new->var_value = NULL;
	new->str = NULL;
	new->next = NULL;
	set_env_list(&new, envp);
	return (new);
}

void	set_env_list(t_env **head, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		get_env(*head, envp[i]);
		i++;
	}
}

void	get_env(t_env *head, char *str)
{
	t_env	*start;
	t_env	*copy;
	int		index;

	copy = copy_env(head, str);
	index = ft_strchr(str, '=') - str + 1;
	if (copy)
	{
		if ((size_t)env_var_name_len(str) == ft_strlen(str))
			return ;
		free(copy->str);
		if (copy->var_value != NULL)
			free(copy->var_value);
		copy->str = ft_strdup(str);
		copy->var_value = ft_substr(str, index, ft_strlen(str));
		return ;
	}
	start = head;
	while (start->next != NULL)
		start = start->next;
	start->next = add_env_node(str);
}

t_env	*add_env_node(char *str)
{
	t_env	*new;
	int		index;

	index = ft_strchr(str, '=') - str;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	new->var_name = ft_substr(str, 0, env_var_name_len(str));
	if (!index)
		new->var_value = NULL;
	else
		new->var_value = ft_substr(str, index + 1, ft_strlen(str));
	new->next = NULL;
	return (new);
}

t_env	*copy_env(t_env *env, char *str)
{
	t_env	*start;
	char	*var_name;
	int		var_name_len;

	var_name = env_var_name(str);
	var_name_len = ft_strlen(var_name);
	start = env->next;
	while (start)
	{
		if (ft_strncmp(start->var_name, var_name, var_name_len + 1) == 0)
		{
			free(var_name);
			return (start);
		}
		start = start->next;
	}
	free(var_name);
	return (NULL);
}
