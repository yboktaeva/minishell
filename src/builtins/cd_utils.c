/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:14:53 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/29 22:28:15 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "builtin.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	no_home_set(t_one_cmd *one_cmd, t_env *env, int *ret)
{
	if (!one_cmd)
	{
		*ret = specific_path_home(env, "HOME");
		if (*ret == -1)
		{
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
			g_status = 1;
		}
	}
}

void	change_path(t_env *env)
{
	char	*tmp;
	t_env	*head;

	head = env->next;
	while (head)
	{
		if (!ft_strcmp(head->var_name, "PWD"))
		{
			tmp = ft_strdup(head->var_value);
			free(head->var_value);
			head->var_value = getcwd(NULL, 0);
		}
		head = head->next;
	}
	head = env->next;
	while (head)
	{
		if (!ft_strcmp(head->var_name, "OLDPWD"))
		{
			free(head->var_value);
			head->var_value = tmp;
		}
		head = head->next;
	}
}

void	print_pwd(t_env *env, char *str)
{
	t_env	*curr;

	curr = env->next;
	while (curr)
	{
		if (!ft_strncmp(curr->var_name, str, ft_strlen(str)))
			printf("%s\n", curr->var_value);
		curr = curr->next;
	}
}

int	specific_path(t_env *env, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path(str, env);
	if (tmp == NULL)
		return (0);
	ret = chdir(tmp);
	if (ret != 0)
	{
		chdir_error(tmp);
		return (ret);
	}
	change_path(env);
	return (ret);
}

char	*find_path(char *str, t_env *env)
{
	t_env	*head;

	head = env->next;
	while (head)
	{
		if (ft_strcmp(head->var_name, str) == 0)
			return (head->var_value);
		head = head->next;
	}
	return (NULL);
}
