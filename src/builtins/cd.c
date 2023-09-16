/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:07:13 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/16 13:57:34 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

static int specific_path(t_table *info, char *str);
static char	*find_path(char *str, t_table *info);
static void	change_path(t_table *info);
static void update_path_variables(t_table *info);
char	*print_path(char *str, char **envp);
int	pwd_oldpwd(t_table *info);

int cmd_cd(t_one_cmd *one_cmd, t_table *info)
{
    int ret;
    char *path;
    char *cwd;

    pwd_oldpwd(info);
    cwd = getcwd(NULL, 0);
    path = NULL;
    t_one_cmd *head = one_cmd->next;
    while (head)
    {
        if (ft_strcmp(head->str, "~") == 0)
            ret = specific_path(info, "HOME");
        else if (ft_strcmp(head->str, "-") == 0)
            ret = specific_path(info, "OLDPWD");
        else
        {
            if (head->str[0] == '/')
            {
                // Absolute path
                path = ft_strdup(head->str);
            }
            else
            {
                // Relative path
                path = ft_strjoin(info->pwd, "/");
                path = ft_strjoin(path, head->str);
            }
        }
        head = head->next;
    }
    if (path)
    {
        ret = chdir(path);
        if (ret != 0)
        {
            perror("chdir");
            printf("Failed to change directory to: %s\n", path);
        }
        else
        {
            printf("avant change_path\n");
            change_path(info);
            printf("apres change_path\n");
            update_path_variables(info);
            printf("apres update_path_variables\n");
        }
        free(path);
    }
    else
    {
        printf("Failed to build path\n");
        ret = -1;
    }
	//free(info->pwd);
	//free(info->old_pwd);
	free(path);
    free(cwd);
    return (ret);
}

static int specific_path(t_table *info, char *str)
{
    char *tmp;
    int ret;

    tmp = find_path(str, info);
    printf("tmp = %s\n", tmp);
    if (tmp == NULL)
    {
        printf("%s not set\n", str);
        return (-1);
    }
    ret = chdir(tmp);
    printf("ret = %d\n", ret);
    free(tmp);
    if (ret != 0)
    {
        perror("chdir");
        printf("Failed to change directory to: %s\n", tmp);
        return (ret);
    }
    // Update info->pwd and info->old_pwd
    change_path(info);
    update_path_variables(info);
    return (ret);
}

static char	*find_path(char *str, t_table *info)
{
    t_env *head;

    head = info->env->next;
	while (head)
	{
		if (ft_strncmp(head->var_name, str, ft_strlen(str)) == 0)
			return (ft_strdup(head->var_value));
        head = head->next;
	}
	return (NULL);
}

static void	change_path(t_table *info)
{
	char	*tmp;

	tmp = ft_strdup(info->pwd);
	free(info->old_pwd);
	info->old_pwd = tmp;
    printf("info->old_pwd %s\n", info->old_pwd);
	free(info->pwd);
	info->pwd = getcwd(NULL, 0);
    printf("info->pwd %s\n", info->pwd);
}

static void update_path_variables(t_table *info)
{
	char	*tmp;
    t_env   *head;

    head = info->env->next;
	while (head)
	{
		if (!ft_strncmp(head->var_name, "PWD", 3))
		{
			tmp = ft_strjoin("PWD=", info->pwd);
			head->str = tmp;
		}
		else if (!ft_strncmp(head->var_name, "OLDPWD", 6) && info->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", info->old_pwd);
			head->str = tmp;
		}
        head = head->next;
	}
	free(tmp);
}

char	*print_path(char *str, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, ft_strlen(str)))
			return (ft_substr(envp[i], ft_strlen(str) + 1, ft_strlen(envp[i]) - ft_strlen(str)));
		i++;
	}
	return (ft_strdup("\0"));
}

int	pwd_oldpwd(t_table *info)
{
    t_env *head;

    head = info->env->next;
	while (head)
	{
		if (ft_strcmp(head->var_name, "PWD") == 0)
		{
			//free(info->pwd);
			info->pwd = ft_substr(head->var_value,
					0, ft_strlen(head->var_value));
		}
		if (ft_strcmp(head->var_name, "OLDPWD") == 0)
		{
			//free(info->old_pwd);
			info->old_pwd = ft_substr(head->var_value,
					0, ft_strlen(head->var_value));
		}
        head = head->next;
	}
	return (1);
}

