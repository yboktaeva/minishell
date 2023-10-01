/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:59:35 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/01 14:52:22 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "exec.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_free_str_array(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*ft_strjoin_free(char *s1, char const *s2, int free_s1)
{
	size_t	i;
	size_t	size;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1) || i < ft_strlen(s2))
	{
		if (i < ft_strlen(s1))
			res[i] = s1[i];
		if (i < ft_strlen(s2))
			res[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	res[size] = '\0';
	if (free_s1)
		free(s1);
	return (res);
}

static int	exec_fail_parent(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	g_status = 127;
	return (g_status);
}

int	if_exec_path(t_parse_list *s, t_table *main, t_cmd_info *cmd_info)
{
	if (ft_strchr(s->one_cmd->str, '/'))
		cmd_info->executable_path = ft_strdup(s->one_cmd->str);
	else
		cmd_info->executable_path = get_executable_path(s->one_cmd->str,
			cmd_info->path);
	if (cmd_info->executable_path == NULL)
		cmd_info->executable_path = ft_strdup(s->one_cmd->str);
	if (cmd_info->executable_path == NULL)
	{
		close_fd_cmd(cmd_info);
		//free(cmd_info->executable_path);
		exec_fail_parent(s->one_cmd->str);
		return (g_status);
	}
	else
	{
		g_status = exec_cmd(s, cmd_info, main);
		if (!g_status)
			return (0);
	}
	return (g_status);
}
