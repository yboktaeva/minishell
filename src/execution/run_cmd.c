/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:06:08 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/09/25 15:11:56 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "utils.h"
#include <unistd.h>

static void	init_cmd_info(t_cmd_info *cmd_info, t_env *env,
				t_parse_list *parse_list);

void	cmd_execution(t_parse_list *parse_list, t_table *main)
{
	t_here_doc	*here_doc;
	t_cmd_info	cmd_info;

	init_cmd_info(&cmd_info, main->env, parse_list);
	main->cmd_info = &cmd_info;
	here_doc = open_heredoc(parse_list);
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
	int	flag_redir;

	flag_redir = 0;
	if (parse_list->input || parse_list->output)
		flag_redir = handle_redirections(parse_list, main->here_doc,
			&cmd_info->in, &cmd_info->out);
	if (flag_redir)
	{
		if (cmd_info->out != STDOUT_FILENO)
		{
			dup2(cmd_info->out, STDOUT_FILENO);
			close(cmd_info->out);
		}
		if (cmd_info->in != STDIN_FILENO)
		{
			dup2(cmd_info->in, STDIN_FILENO);
			close(cmd_info->in);
		}
	}
	builtin_exec(parse_list->one_cmd, main->env, ONE_CMD);
}

static void	init_cmd_info(t_cmd_info *cmd_info, t_env *env,
		t_parse_list *parse_list)
{
	cmd_info->path = get_path_from_envp(env);
	cmd_info->nb_cmds = cmd_size(parse_list);
	cmd_info->in = 0;
	cmd_info->out = 1;
}