/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:07:13 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/29 22:17:56 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "builtin.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	init_cmd_cd(char **path, int *ret);
static int	handle_tilde_and_dash(t_one_cmd *head, t_env *curr);
static char	*create_path(t_one_cmd *head, t_env *curr);
static int	change_directory(char *path, t_env *env, t_one_cmd *one_cmd);

int	cmd_cd(t_one_cmd *one_cmd, t_env *env)
{
	int			ret;
	char		*path;
	t_one_cmd	*head;
	t_env		*curr;

	head = one_cmd->next;
	curr = env->next;
	init_cmd_cd(&path, &ret);
	no_home_set(head, curr, &ret);
	while (head)
	{
		ret = handle_tilde_and_dash(head, curr);
		if (ret == -1)
		{
			path = create_path(head, curr);
			if (path)
				ret = change_directory(path, curr, head);
		}
		head = head->next;
	}
	free(path);
	return (ret);
}

static void	init_cmd_cd(char **path, int *ret)
{
	*path = NULL;
	*ret = -1;
}

static int	handle_tilde_and_dash(t_one_cmd *head, t_env *curr)
{
	int	ret;

	ret = -1;
	if (!ft_strcmp(head->str, "~"))
		ret = specific_path(curr, "HOME");
	else if (!ft_strcmp(head->str, "-"))
	{
		ret = specific_path(curr, "OLDPWD");
		print_pwd(curr, "PWD");
	}
	return (ret);
}

static char	*create_path(t_one_cmd *head, t_env *curr)
{
	char	*path;
	char	*tmp;

	path = NULL;
	tmp = NULL;
	if (head->str[0] == '/')
		path = ft_strdup(head->str);
	else
	{
		while (curr)
		{
			if (!ft_strcmp(curr->var_name, "PWD"))
			{
				tmp = ft_strjoin(curr->var_value, "/");
				path = ft_strjoin(tmp, head->str);
			}
			curr = curr->next;
		}
		free(tmp);
	}
	return (path);
}

static int	change_directory(char *path, t_env *env, t_one_cmd *one_cmd)
{
	int	ret;

	ret = chdir(path);
	if (ret != 0)
		chdir_error(one_cmd->str);
	else
		change_path(env);
	return (ret);
}
