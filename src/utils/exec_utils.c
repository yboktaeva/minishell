/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:56:18 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/17 18:28:42 by yuliaboktae      ###   ########.fr       */
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
	char	**cp_envp;

	i = 0;
	head = env->next;
	cp_envp = (char **)malloc((env_size(env) + 2) * sizeof(char *));
	if (!cp_envp)
	{
		perror("Malloc failure in duplicate envp");
		return (NULL);
	}
	while (head)
	{
		cp_envp[i] = head->str;
		i++;
		head = head->next;
	}
	cp_envp[i] = NULL;
	return (cp_envp);
}
