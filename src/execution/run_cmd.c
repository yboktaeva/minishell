/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:06:08 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/09/27 11:21:24 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	init_cmd_info(t_cmd_info *cmd_info, t_env *env,
				t_parse_list *parse_list);

void	cmd_execution(t_parse_list *parse_list, t_table *main)
{
	t_here_doc	*here_doc;
	t_cmd_info	cmd_info;
	
	init_cmd_info(&cmd_info, main->env, parse_list);
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

void	one_builtin(t_parse_list *parse_list, t_table *main, t_cmd_info *cmd_info)
{
    int flag_redir;
    int	tmp_fd[2];
	
    tmp_fd[0] = dup(STDIN_FILENO);
    tmp_fd[1] = dup(STDOUT_FILENO);
	flag_redir = 0;
	if (parse_list->input || parse_list->output)
		flag_redir = handle_redirections(parse_list, main->here_doc,
			&cmd_info->in, &cmd_info->out);
	if (flag_redir)
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
	}
	builtin_exec(parse_list->one_cmd, main->env, ONE_CMD, main);
	if (flag_redir)
    {
        dup2(tmp_fd[0], STDIN_FILENO);
        dup2(tmp_fd[1], STDOUT_FILENO);
    }
	close(tmp_fd[0]);
	close(tmp_fd[1]);
}

static void	init_cmd_info(t_cmd_info *cmd_info, t_env *env,
		t_parse_list *parse_list)
{
    cmd_info->fd = malloc(sizeof(int) * 2);
	if (!cmd_info->fd)
		perror("fd: malloc failed");
    cmd_info->fd[0] = -1;
    cmd_info->fd[1] = -1;
	cmd_info->path = get_path_from_envp(env);
	cmd_info->nb_cmds = cmd_size(parse_list);
	cmd_info->in = 0;
	cmd_info->out = 1;
}