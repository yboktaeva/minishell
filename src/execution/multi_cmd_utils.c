/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:54:25 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/25 15:17:20 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "exec.h"
#include "parser.h"
#include "builtin.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void exec_comds(const char *path, t_arg *arg)
{
    execve(path, arg->argv, arg->envp);
    perror("Erreur lors de l'exécution de la commande");
    exit(EXIT_FAILURE);
}

void ft_close(int fd)
{
    if (fd > 0)
        close(fd);
}

void close_fd_cmd(t_cmd_info *cmd_info)
{
    ft_close(cmd_info->fd[1]);
    ft_close(cmd_info->fd[0]);
    if (cmd_info->in != STDIN_FILENO)
        ft_close(cmd_info->in);
    if (cmd_info->out != STDOUT_FILENO)
        ft_close(cmd_info->out);
}

int wait_all_pid(t_cmd_info *cmd_info, pid_t pid, pid_t *pids)
{
    int save_status;
    int status;
    int wpid;
    int i;
    
    save_status = 0;
    status = 1;
    wpid = 0;
    i = 0;
    while (i < cmd_info->nb_cmds)
    {
        wpid = waitpid(pids[i], &status, 0);
        if (pid == wpid)
            save_status = status;
        i++;
    }
    if (WIFSIGNALED(save_status))
        status = 128 + WTERMSIG(save_status);
    else if (WIFEXITED(save_status))
        status = WEXITSTATUS(save_status);
    else
        status = save_status;
    return (status);
}

void reset_cmd_info(t_cmd_info *cmd_info)
{
    cmd_info->out = STDOUT_FILENO;
    cmd_info->in = STDIN_FILENO;
}
