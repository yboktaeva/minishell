/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:21:40 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/30 09:43:12 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include <stdlib.h>

static void	check_fd_free(t_table *main);

int	is_builtin(t_one_cmd *one_cmd)
{
	if (one_cmd == NULL)
		return (0);
	if (ft_strcmp(one_cmd->str, "exit") == 0)
		return (1);
	else if (ft_strcmp(one_cmd->str, "echo") == 0)
		return (1);
	else if (ft_strcmp(one_cmd->str, "cd") == 0)
		return (1);
	else if (ft_strcmp(one_cmd->str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(one_cmd->str, "export") == 0)
		return (1);
	else if (ft_strcmp(one_cmd->str, "unset") == 0)
		return (1);
	else if (ft_strcmp(one_cmd->str, "env") == 0)
		return (1);
	return (0);
}

void	builtin_exec(t_one_cmd *one_cmd, t_env *env,
		t_num_cmd num_of_cmd, t_table *main)
{
	int	b_status;

	b_status = 0;
	if (ft_strcmp(one_cmd->str, "echo") == 0)
		b_status = cmd_echo(one_cmd);
	else if (ft_strcmp(one_cmd->str, "cd") == 0)
		b_status = cmd_cd(one_cmd, env);
	else if (ft_strcmp(one_cmd->str, "pwd") == 0)
		b_status = cmd_pwd(one_cmd);
	else if (ft_strcmp(one_cmd->str, "export") == 0)
		b_status = cmd_export(one_cmd, env);
	else if (ft_strcmp(one_cmd->str, "unset") == 0)
		b_status = cmd_unset(one_cmd, env);
	else if (ft_strcmp(one_cmd->str, "env") == 0)
		b_status = cmd_env(env);
	else if (ft_strcmp(one_cmd->str, "exit") == 0)
		b_status = cmd_exit(one_cmd, main);
	if (num_of_cmd == ONE_CMD)
		g_status = b_status;
	else
		exit (b_status);
	check_fd_free(main);
	return ;
}

static void	check_fd_free(t_table *main)
{
	if (main->cmd_info->fd != NULL)
	{
		free(main->cmd_info->fd);
		main->cmd_info->fd = NULL;
	}
}
