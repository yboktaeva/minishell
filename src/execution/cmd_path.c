/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:03:01 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/27 17:20:12 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static const char	*prepare_path(const char *path);
static char			**get_table_of_paths(const char *path);
static char			*create_executable_path(const char *path, const char *cmd);
static char			*find_executable(char **dirs, const char *cmd);

char	*get_executable_path(const char *cmd, const char *path)
{
	char **dirs;
	char *executable_path;

	path = prepare_path(path);
	if (path == NULL)
		return (NULL);
	dirs = get_table_of_paths(path);
	if (!dirs)
		return (NULL);
	executable_path = find_executable(dirs, cmd);
	ft_free_str_array(dirs);
	return (executable_path);
}

static const char	*prepare_path(const char *path)
{
	if (path == NULL || *path == '\0')
		return (NULL);
	while (*path && *path == ' ')
		path++;
	if (ft_strncmp(path, "PATH=", 5) == 0)
		path += 5;
	return (path);
}

static char	**get_table_of_paths(const char *path)
{
	char	**table;

	table = ft_split_ignore_spaces(path, ':');
	return (table);
}

static char	*find_executable(char **dirs, const char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		cmd_path = create_executable_path(dirs[i], cmd);
		if (!cmd_path)
			break ;
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

static char	*create_executable_path(const char *path, const char *cmd)
{
	char	*executable_path;
	char	*cmd_path;

	executable_path = ft_strjoin(path, "/");
	if (!executable_path)
		return (NULL);
	cmd_path = ft_strjoin_free(executable_path, cmd, 1);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}
