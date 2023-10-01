/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:06:08 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/10/01 19:55:18 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include "exec.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	init_cmd_info(t_cmd_info *cmd_info, t_parse_list *s);
static void	execute_exit(t_parse_list *s, t_table *main);
static void	execute_command(t_parse_list *s, t_table *main,
				int flag_redir, int *tmp_fd);

void	cmd_execution(t_parse_list *parse_list, t_table *main)
{
	t_here_doc	*here_doc;
	t_cmd_info	cmd_info;

	init_cmd_info(&cmd_info, parse_list);
	main->cmd_info = &cmd_info;
	here_doc = open_heredoc(parse_list, &cmd_info);
	main->here_doc = here_doc;
	if (cmd_info.nb_cmds == 1)
	{
		if (is_builtin(parse_list->one_cmd))
			one_builtin(parse_list, main, &cmd_info);
		else
			one_cmd_exec(parse_list, main, &cmd_info);
	}
	else
		multi_cmds_exec(parse_list, main, &cmd_info);
	free_n_close_heredoc(here_doc, 0);
	return ;
}

void	one_builtin(t_parse_list *parse_list,
		t_table *main, t_cmd_info *cmd_info)
{
	int	flag_redir;
	int	tmp_fd[2];

	execute_exit(parse_list, main);
	tmp_fd[0] = dup(STDIN_FILENO);
	tmp_fd[1] = dup(STDOUT_FILENO);
	flag_redir = handle_io_redir(parse_list, main, cmd_info);
	execute_command(parse_list, main, flag_redir, tmp_fd);
}

static void	init_cmd_info(t_cmd_info *cmd_info, t_parse_list *s)
{
	cmd_info->fd[0] = -1;
	cmd_info->fd[1] = -1;
	cmd_info->nb_cmds = cmd_size(s);
	cmd_info->in = 0;
	cmd_info->out = 1;
}

static void	execute_exit(t_parse_list *s, t_table *main)
{
	if (ft_strcmp(s->one_cmd->str, "exit") == 0)
		builtin_exec(s->one_cmd, main->env, ONE_CMD, main);
}

static void	execute_command(t_parse_list *s, t_table *main,
			int flag_redir, int *tmp_fd)
{
	builtin_exec(s->one_cmd, main->env, ONE_CMD, main);
	if (flag_redir)
	{
		dup2(tmp_fd[0], STDIN_FILENO);
		dup2(tmp_fd[1], STDOUT_FILENO);
	}
	close(tmp_fd[0]);
	close(tmp_fd[1]);
}
