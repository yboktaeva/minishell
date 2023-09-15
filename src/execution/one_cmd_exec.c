/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:57:21 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/15 14:57:53 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

char        *get_path_from_envp(t_arg *arg);
static int  one_cmd(const char *path, t_parse_list *s, t_arg *arg);
static void exec_comd(const char *path, t_parse_list *parse_list, t_arg *arg, int fd_in, int fd_out);
static int  wait_and_get_exit_status(pid_t pid);

int one_cmd_exec(t_parse_list *parse_list, t_arg *arg)
{
    const char *path;
    char        *executable_path;

    path = get_path_from_envp(arg);
    //int i = 0;
    //while (parse_list)
    {
        executable_path = get_executable_path(parse_list->one_cmd->str, path);
        if (!executable_path)
        {
        // printf("Commande introuvable : %s\n", command);
            exit(EXIT_FAILURE);
        }
        one_cmd(executable_path, parse_list, arg);
        //parse_list = parse_list->next;
        //free(executable_path);
    }
    return (0);
}

static int one_cmd(const char *path, t_parse_list *parse_list, t_arg *arg) 
{
    //int pipe_fd[2];
    pid_t pid;
    int status;
    int fd_in;
    int fd_out;
    //t_here_doc *here_doc;
    
    
    pid = fork();
    fd_in = STDIN_FILENO;
    fd_out = STDOUT_FILENO;
    //here_doc = open_heredoc(parse_list);
    // if (pipe(pipe_fd) == -1) 
    // {
    //     perror("Erreur lors de la création du tube");
    //     return (-1);
    // }
    if (pid == -1) 
    {
        perror("Erreur lors de la création du processus enfant");
        return (-1);
    } 
    else if (pid == 0)
    {
        create_args(parse_list, arg);
        exec_comd(path, parse_list, arg, fd_in, fd_out);
    }
    // close(pipe_fd[1]);
    // close(pipe_fd[0]);
    status = wait_and_get_exit_status(pid);
    return (status);
}

static int wait_and_get_exit_status(pid_t pid)
{
    int status;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    else
    {
        printf("La commande ne s'est pas terminée normalement.\n");
        return (-1);
    }
}

static void exec_comd(const char *path, t_parse_list *parse_list, t_arg *arg, int fd_in, int fd_out) 
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
    handle_redirections(parse_list, &fd_in, &fd_out);
    execve(path, arg->argv, arg->envp);
    perror("Erreur lors de l'exécution de la commande");
    exit(1);
}

char    *get_path_from_envp(t_arg *arg)
{
    char    *path;
    int i;
   
    path = NULL;
    i = 0;
    
    while (arg->envp[i])
    {
        if (ft_strncmp("PATH=", arg->envp[i], 5) == 0)
        {
            path = (ft_strdup(arg->envp[i] + 5));
            if (path == NULL)
            {
                perror("Erreur d'allocation de mémoire");
                exit(EXIT_FAILURE);
            }
            break;
        }
        i++;
    }
    return (path);
}