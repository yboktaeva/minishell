/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:57:21 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/26 10:46:19 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "minishell.h"
#include "utils.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

static int	one_cmd(const char *path, t_parse_list *s, t_table *main, t_cmd_info *cmd_info);
static void	exec_comd(const char *path, t_arg *arg, t_cmd_info *cmd_info);
static int	wait_and_get_exit_status(pid_t pid);

int	one_cmd_exec(t_parse_list *parse_list, t_table *main, t_cmd_info *cmd_info)
{
	//int		status;

	//status = 0;
	if (parse_list->one_cmd == NULL)
		return (0);
	cmd_info->executable_path = get_executable_path(parse_list->one_cmd->str, cmd_info->path);
	if (cmd_info->executable_path == NULL)
	{
		command_not_found(parse_list->one_cmd->str);
		free(cmd_info->executable_path);
		return (g_status);
	}
	else
		g_status = one_cmd(cmd_info->executable_path, parse_list, main, cmd_info);
	free(cmd_info->executable_path);
	return (g_status);
}

static int	one_cmd(const char *path, t_parse_list *parse_list, t_table *main, t_cmd_info *cmd_info)
{
	pid_t	pid;
	int		status;
	// int		fd_in;
	// int		fd_out;
	

	handle_sig(SIG_PARENT);
	pid = fork();
	// fd_in = STDIN_FILENO;
	// fd_out = STDOUT_FILENO;
	if (pid == -1)
	{
		perror("Fork failed");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		handle_sig(SIG_CHILD);
		create_args(parse_list, main->arg);
    	handle_redirections(parse_list, main->here_doc, &cmd_info->in, &cmd_info->out);
		exec_comd(path, main->arg, cmd_info);
	}
	status = wait_and_get_exit_status(pid);
	return (status);
}

static int	wait_and_get_exit_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
	{
		printf("La commande ne s'est pas terminée normalement.\n");
		return (-1);
	}
}

static void	exec_comd(const char *path, t_arg *arg, t_cmd_info *cmd_info)
{
	if (cmd_info->in != STDIN_FILENO)
	{
		dup2(cmd_info->in, STDIN_FILENO);
		close(cmd_info->in);
	}
	if (cmd_info->out != STDOUT_FILENO)
	{
		dup2(cmd_info->out, STDOUT_FILENO);
		close(cmd_info->out);
	}
	if (execve(path, arg->argv, arg->envp) == -1)
		exec_fail();
}