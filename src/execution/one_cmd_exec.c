/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:57:21 by asekmani          #+#    #+#             */
/*   Updated: 2023/10/01 19:27:08 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "builtin.h"
#include "exec.h"
#include "minishell.h"
#include "utils.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int	one_cmd(const char *path, t_parse_list *s, t_table *main,
				t_cmd_info *cmd_info);
static void	exec_comd(t_table *main, const char *path, t_arg *arg,
				t_cmd_info *cmd_info);
static int	wait_and_get_exit_status(pid_t pid);

int	one_cmd_exec(t_parse_list *s, t_table *main, t_cmd_info *cmd_info)
{
	cmd_info->path = get_path_from_envp(main->env);
	if (cmd_info->path == NULL)
	{
		path_null(s->one_cmd->str);
		return (g_status);
	}
	if (s->one_cmd == NULL)
		return (0);
	if (ft_strchr(s->one_cmd->str, '/'))
		cmd_info->executable_path = ft_strdup(s->one_cmd->str);
	else
		cmd_info->executable_path = get_executable_path(s->one_cmd->str,
				cmd_info->path);
	if (cmd_info->executable_path == NULL)
		cmd_info->executable_path = ft_strdup(s->one_cmd->str);
	g_status = one_cmd(cmd_info->executable_path, s, main,
			cmd_info);
	free(cmd_info->executable_path);
	return (g_status);
}

static int	one_cmd(const char *path, t_parse_list *parse_list, t_table *main,
		t_cmd_info *cmd_info)
{
	pid_t	pid;
	int		status;

	status = 0;
	handle_sig(SIG_PARENT);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		safe_exit(main);
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		handle_sig(SIG_CHILD);
		create_args(parse_list, main->arg);
		handle_redirections(parse_list, main->here_doc, &cmd_info->in,
			&cmd_info->out);
		exec_comd(main, path, main->arg, cmd_info);
	}
	else
		status = wait_and_get_exit_status(pid);
	handle_sig(SIG_PARENT);
	return (status);
}

static int	wait_and_get_exit_status(pid_t pid)
{
	int	status;

	status = -1;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
	{
		g_status = 127;
		return (g_status);
	}
}

static void	exec_comd(t_table *main, const char *path, t_arg *arg,
				t_cmd_info *cmd_info)
{
	if (cmd_info->in != STDIN_FILENO)
	{
		dup2(cmd_info->in, STDIN_FILENO);
		ft_close(cmd_info->in);
	}
	if (cmd_info->out != STDOUT_FILENO)
	{
		dup2(cmd_info->out, STDOUT_FILENO);
		ft_close(cmd_info->out);
	}
	if (execve(path, arg->argv, arg->envp) == -1)
		exec_fail(main, *arg->argv);
}
