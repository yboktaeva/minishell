/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:07:13 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/17 18:18:36 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

static int specific_path(t_env *env, char *str);
static char	*find_path(char *str, t_env *env);
static void	change_path(t_env *env);
static void update_path_variables(t_env *env);
//char	*print_path(char *str, char **envp);

int cmd_cd(t_one_cmd *one_cmd, t_env *env)
{
    int ret;
    char *path;
    char *cwd;

    cwd = getcwd(NULL, 0);
    path = NULL;
    t_one_cmd *head = one_cmd->next;
    t_env   *curr = env->next;
    while (head)
    {
        if (ft_strcmp(head->str, "~") == 0)
            ret = specific_path(env, "HOME");
        else if (ft_strcmp(head->str, "-") == 0)
            ret = specific_path(env, "OLDPWD");
        else
        {
            if (head->str[0] == '/')
            {
                // Absolute path
                path = ft_strdup(head->str);
            }
            else
            {
                while (curr)
                {
                    if (!ft_strcmp(curr->var_name, "PWD"))
                    {
                        path = ft_strjoin(curr->var_value, "/");
                        path = ft_strjoin(path, head->str);
                    }
                    curr = curr->next;
                }
                if (path)
                {
                    ret = chdir(path);
                    if (ret != 0)
                        perror("chdir");
                    else
                    {
                        change_path(env);
                        update_path_variables(env);
                    }
                    free(path);
                }
                else
                    ret = -1;
            }
        }
        head = head->next;
    }
    free(cwd);
    return (ret);
}

static int specific_path(t_env *env, char *str)
{
    char *tmp;
    int ret;

    tmp = find_path(str, env);
    if (tmp == NULL)
        return (-1);
    ret = chdir(tmp);
    if (ret != 0)
    {
        perror("chdir");
        return (ret);
    }
    change_path(env);
    update_path_variables(env);
    return (ret);
}

static char	*find_path(char *str, t_env *env)
{
    t_env *head;

    head = env->next;
	while (head)
	{
		if (ft_strcmp(head->var_name, str) == 0)
			return (head->var_value);
        head = head->next;
	}
	return (NULL);
}

static void	change_path(t_env *env)
{
	char	*tmp = NULL;
    t_env   *head;

    head = env->next;
    while (head)
    {
        if (!ft_strcmp(head->var_name, "PWD"))
        {
            tmp = ft_strdup(head->var_value);
            free(head->var_value);
            head->var_value = getcwd(NULL, 0);
        }
        if (!ft_strcmp(head->var_name, "OLDPWD"))
        {
            free(head->var_value);
            head->var_value = tmp;
        }
        head = head->next;
    }
}

static void update_path_variables(t_env *env)
{
	char	*tmp;
    t_env   *head;

    head = env->next;
	while (head)
	{
		if (!ft_strncmp(head->var_name, "PWD", 3))
		{
			tmp = ft_strjoin("PWD=", env->var_value);
			head->str = tmp;
		}
		else if (!ft_strncmp(head->var_name, "OLDPWD", 6) && env->var_value)
		{
			tmp = ft_strjoin("OLDPWD=", env->var_value);
			head->str = tmp;
		}
        head = head->next;
	}
	free(tmp);
}

// char	*print_path(char *str, char **envp)
// {
// 	int		i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (!ft_strncmp(envp[i], str, ft_strlen(str)))
// 			return (ft_substr(envp[i], ft_strlen(str) + 1, ft_strlen(envp[i]) - ft_strlen(str)));
// 		i++;
// 	}
// 	return (ft_strdup("\0"));
// }
