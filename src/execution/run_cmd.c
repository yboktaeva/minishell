/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:06:08 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/09/24 01:34:12 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include "utils.h"

void cmd_execution(t_parse_list *parse_list, t_table *info, t_env *env, t_arg *arg)
{
    int n_cmd;
    int fd_in;
    int fd_out;
    t_here_doc *here_doc;
    
    fd_in = 0;
    fd_out = 1;
    here_doc = open_heredoc(parse_list);
    info->here_doc = here_doc;
    n_cmd = cmd_size(parse_list);
    if (n_cmd == 1)
    {
        if (is_builtin(parse_list->one_cmd))
            one_builtin(parse_list, env, fd_in, fd_out);
        else
            one_cmd_exec(parse_list, arg, env);
    }
    else
    {
        multi_cmds_exec(parse_list, arg, env, info->cmd_info);
    }
    free_n_close_heredoc(here_doc, 0);
    return ;
}

void    one_builtin(t_parse_list *parse_list, t_env *env, int fd_in, int fd_out)
{
    int tmp_fd[2];
    int flag_redir;
    
    tmp_fd[0] = dup(STDIN_FILENO);
    tmp_fd[1] = dup(STDOUT_FILENO);
    dup2(STDIN_FILENO, tmp_fd[0]);
	dup2(STDOUT_FILENO, tmp_fd[1]);
    flag_redir = 1;
    if (parse_list->input || parse_list->output)
        flag_redir = handle_redirections(parse_list, &fd_in, &fd_out);
    if (flag_redir)
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
    }
    builtin_exec(parse_list->one_cmd, env, ONE_CMD);
    //dup2(tmp_fd[0], STDIN_FILENO);
    close(tmp_fd[0]);
	//dup2(tmp_fd[1], STDOUT_FILENO);
    close(tmp_fd[1]);
}


