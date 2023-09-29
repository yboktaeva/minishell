/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:08:13 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/29 21:31:23 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "exec.h"
#include "parser.h"
#include "builtin.h"
#include "utils.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

static int execute_parent(t_cmd_info *cmd_info, pid_t pid, int *fdc);
static void execute_child(t_cmd_info *cmd_info, int *fdc, const char *path, t_arg *arg);
static int execute_command(t_parse_list *parse_list, const char *path, t_table *main);
static int exec_cmd(t_parse_list *parse_list, t_cmd_info *cmd_info, t_table *main);

int multi_cmds_exec(t_parse_list *parse_list, t_table *main, t_cmd_info *cmd_info)
{
    cmd_info->index_cmd = 1;
    while (parse_list)
    {
        if (parse_list->one_cmd)
        {
            if (!cmd_info->path)
		        path_null(parse_list->one_cmd->str);
            else
            {
                cmd_info->executable_path = get_executable_path(parse_list->one_cmd->str, cmd_info->path);
                if (cmd_info->executable_path == NULL)
                {
                    close_fd_cmd(cmd_info);
                }
                else
                {
                    g_status = exec_cmd(parse_list, cmd_info, main);
                    if(!g_status)
                    {
                        return (0);
                    }
                }
            }
        }
        parse_list = parse_list->next;
        cmd_info->index_cmd++;
    }
    return (g_status);
}

static int exec_cmd(t_parse_list *parse_list, t_cmd_info *cmd_info, t_table *main)
{
    int status;

    status = 0;
    reset_cmd_info(cmd_info);
    status = handle_redirections(parse_list, main->here_doc, &(main->cmd_info)->in, &(main->cmd_info)->out);
    if (status)
        status = execute_command(parse_list, main->cmd_info->executable_path, main);
    reset_cmd_info(main->cmd_info);
    free(cmd_info->executable_path);
    return (status);
}

static int execute_command(t_parse_list *parse_list, const char *path, t_table *main)
{
    pid_t pid;
    int res;
    int *fdc;
    int status;

    res = -1;
    fdc = malloc(sizeof(int) * 2);
    res = pipe(fdc);
    if (res == -1)
    {
        exit(1);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("Fork failed");
        return (EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        status = 0;
        handle_sig(SIG_CHILD);
        create_args(parse_list, main->arg);
        execute_child(main->cmd_info, fdc, path, main->arg);
    }
    status = execute_parent(main->cmd_info, pid, fdc);
    return (status);
}

static int execute_parent(t_cmd_info *cmd_info, pid_t pid, int *fdc)
{
    int status;

    status = 1;
    handle_sig(SIG_PARENT);
    close_fd_cmd(cmd_info);
    if (cmd_info->index_cmd == cmd_info->nb_cmds)
    {
        ft_close(fdc[0]);
        ft_close(fdc[1]);
        status = wait_all_pid(cmd_info, pid);
        check_free(fdc);
        check_free(cmd_info->fd);
       
    }
    else
    {
        check_free(cmd_info->fd);
        cmd_info->fd = fdc;
    }
    return (status);
}

static void execute_child(t_cmd_info *cmd_info, int *fdc, const char *path, t_arg *arg)
{
    if (cmd_info->in != STDIN_FILENO)
    {
        dup2(cmd_info->in, STDIN_FILENO);
        ft_close(cmd_info->in);
    }
    else if (cmd_info->index_cmd > 1 && cmd_info->fd[0] != -1)
    {
        dup2(cmd_info->fd[0], STDIN_FILENO);
        ft_close(cmd_info->fd[1]);
    }
    if (cmd_info->out != STDOUT_FILENO)
        dup2(cmd_info->out, STDOUT_FILENO);
    else if (cmd_info->index_cmd != cmd_info->nb_cmds)
    {
        ft_close(fdc[0]);
        dup2(fdc[1], STDOUT_FILENO);
        ft_close(fdc[1]);
    }
    execve(path, arg->argv, arg->envp);
}
