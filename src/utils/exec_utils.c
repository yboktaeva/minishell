/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:56:18 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/27 17:20:29 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int	cmd_size(t_parse_list *parse_list)
{
	t_parse_list	*tmp;
	int				len;

	len = 0;
	tmp = parse_list;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

int	num_args(t_one_cmd *one_cmd)
{
	int	len;

	len = 0;
	while (one_cmd)
	{
		len++;
		one_cmd = one_cmd->next;
	}
	return (len);
}

int	env_size(t_env *env)
{
	int		len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

char	**duplicate_envp(t_env *env)
{
	int		i;
	t_env	*head;
	char	**fake_envp;

	i = 0;
	if (env == NULL)
		return (NULL);
	head = env->next;
	fake_envp = (char **)malloc((env_size(env) + 2) * sizeof(char *));
	if (!fake_envp)
	{
		perror("duplicate envp: malloc failed");
		return (NULL);
	}
	while (head)
	{
		fake_envp[i] = head->str;
		i++;
		head = head->next;
	}
	fake_envp[i] = NULL;
	return (fake_envp);
}

char	*get_path_from_envp(t_env *env)
{
	char *path;
	t_env *head;
	
	path = NULL;
	if (!env)
		return (NULL);
	head = env->next;
	while (head)
	{
		if (ft_strcmp(head->var_name, "PATH") == 0)
		{
			if (head->str)
				path = head->str;
			else
				path = ft_strdup("\0");	
		}
		head = head->next;
	}
	return (path);
}