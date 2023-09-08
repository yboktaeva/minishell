/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:07:13 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/08 18:55:55 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>

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
	int	i;

	i = 0;
	while (info->envp[i])
	{
		if (!ft_strncmp(info->envp[i], "PWD=", 4))
		{
			//free(info->pwd);
			info->pwd = ft_substr(info->envp[i],
					4, ft_strlen(info->envp[i]) - 4);
		}
		if (!ft_strncmp(info->envp[i], "OLDPWD=", 7))
		{
			//free(info->old_pwd);
			info->old_pwd = ft_substr(info->envp[i],
					7, ft_strlen(info->envp[i]) - 7);
		}
		i++;
	}
	return (1);
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

static char	*find_path(char *str, t_table *info)
{
	int	i;

	i = 0;
	while (info->envp[i])
	{
		if (ft_strncmp(info->envp[i], str, ft_strlen(str)) == 0)
			return ft_strdup(info->envp[i] + ft_strlen(str));
		i++;
	}
	return (NULL);
}

static void update_path_variables(t_table *info)
{
	int		i;
	char	*tmp;
    //char    **env_tmp;

    //env_tmp = info->envp;
	i = 0;
	while (info->envp[i])
	{
		if (!ft_strncmp(info->envp[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", info->pwd);
			//free(info->envp[i]);
			info->envp[i] = tmp;
		}
		else if (!ft_strncmp(info->envp[i], "OLDPWD=", 7) && info->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", info->old_pwd);
			//free(info->envp[i]);
			info->envp[i] = tmp;
		}
		i++;
	}
	//free(env_tmp);
}

/*static void update_path_variables(t_table *info)
{
    int i;
    char *tmp;
    char **env_tmp;

    env_tmp = info->envp;
    i = 0;
    while (env_tmp[i])
    {
        if (!ft_strncmp(env_tmp[i], "PWD=", 4))
        {
            tmp = ft_strjoin("PWD=", info->pwd);
            //free(info->envp[i]);
            info->envp[i] = tmp;
            break;
        }
        i++;
    }
    i = 0; // Reset i for updating OLDPWD
    while (env_tmp[i])
    {
        if (!ft_strncmp(env_tmp[i], "OLDPWD=", 7) && info->old_pwd)
        {
            tmp = ft_strjoin("OLDPWD=", info->old_pwd);
            //free(info->envp[i]);
            info->envp[i] = tmp;
            break;
        }
        i++;
    }
}*/
/*static int	specific_path(t_table *info, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path(str, info);
    printf("tmp = %s\n", tmp);
    if (tmp == NULL)
    {
        fprintf(stderr, "%s not set\n", str);
        return (-1);
    }
	ret = chdir(tmp);
	printf("ret = %d\n", ret);
	free(tmp);
	if (ret != 0)
	{
		perror("chdir");
        fprintf(stderr, "Failed to change directory to: %s\n", tmp);
	}
	return (ret);
}*/

static int specific_path(t_table *info, char *str)
{
    char *tmp;
    int ret;

    tmp = find_path(str, info);
    printf("tmp = %s\n", tmp);
    if (tmp == NULL)
    {
        fprintf(stderr, "%s not set\n", str);
        return (-1);
    }
    ret = chdir(tmp);
    printf("ret = %d\n", ret);
    free(tmp);
    if (ret != 0)
    {
        perror("chdir");
        fprintf(stderr, "Failed to change directory to: %s\n", tmp);
        return (ret);
    }

    // Update info->pwd and info->old_pwd
    change_path(info);
    update_path_variables(info);

    return (ret);
}

int cmd_cd(t_table *info, char *arg)
{
    int ret;
    char *path;
    char *cwd;

    cwd = getcwd(NULL, 0);
    path = NULL;

    if (!arg || ft_strcmp(arg, "~") == 0)
        ret = specific_path(info, "HOME=");
	else if (ft_strcmp(arg, "-") == 0)
        ret = specific_path(info, "OLDPWD=");
	else
	{
        if (arg[0] == '/')
		{
            // Absolute path
            path = ft_strdup(arg);
        }
		else
		{
            // Relative path
            path = ft_strjoin(info->pwd, "/");
            path = ft_strjoin(path, arg);
        }

        if (path)
		{
            ret = chdir(path);
            if (ret != 0)
			{
                perror("chdir");
                fprintf(stderr, "Failed to change directory to: %s\n", path);
            }
			else
			{
                printf("avant change_path\n");
                change_path(info);
                printf("apres change_path\n");
                update_path_variables(info);
                printf("apres update_path_variables\n");
            }
            //free(path);
        }
		else
		{
            fprintf(stderr, "Failed to build path\n");
            ret = -1;
        }
    }
	//free(info->pwd);
	//free(info->old_pwd);
	free(path);
    free(cwd);
    return ret;
}