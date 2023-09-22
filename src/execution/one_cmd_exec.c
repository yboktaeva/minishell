/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:57:21 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/22 11:32:39 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "minishell.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int	one_cmd(const char *path, t_parse_list *s, t_arg *arg);
static void	exec_comd(const char *path, t_arg *arg,
				int fd_in, int fd_out);
static int	wait_and_get_exit_status(pid_t pid);

int	one_cmd_exec(t_parse_list *parse_list, t_arg *arg, t_env *env)
{
	const char	*path;
	char		*executable_path;

	path = get_path_from_envp(env);
	executable_path = get_executable_path(parse_list->one_cmd->str, path);
	if (!executable_path)
	{
		printf("%s : command not found\n", parse_list->one_cmd->str);
		free(executable_path);
		g_status = 127;
		return (g_status);
	}
	else
		one_cmd(executable_path, parse_list, arg);
	free(executable_path);
	return (0);
}

static int	one_cmd(const char *path, t_parse_list *parse_list, t_arg *arg)
{
	pid_t	pid;
	int		status;
	int		fd_in;
	int		fd_out;

	// t_here_doc *here_doc;
	handle_sig(SIG_PARENT);
	pid = fork();
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	// here_doc = open_heredoc(parse_list);
	if (pid == -1)
	{
		perror("Erreur lors de la création du processus enfant");
		return (-1);
	}
	else if (pid == 0)
	{
		handle_sig(SIG_CHILD);
		create_args(parse_list, arg);
		handle_redirections(parse_list, &fd_in, &fd_out);
		exec_comd(path, arg, fd_in, fd_out);
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

static void	exec_comd(const char *path, t_arg *arg,
		int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (execve(path, arg->argv, arg->envp) == -1)
		perror("Execve error");
}

char	*get_path_from_envp(t_env *env)
{
	char *path;
	t_env *head;
	
	path = NULL;
	if (!env)
		return (NULL);
	head = env->next;
	while (head)
	{
		if (ft_strcmp(head->var_name, "PATH") == 0)
		{
			if (head->var_value)
				path = ft_strdup(head->var_value);
			else
				path = ft_strdup("\0");	
		}
		head = head->next;
	}
	return (path);
}