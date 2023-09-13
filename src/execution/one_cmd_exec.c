/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:57:21 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/14 00:08:09 by yuliaboktae      ###   ########.fr       */
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
static void exec_comd(const char *path, t_arg *arg, int fd_in, int fd_out);

int one_cmd_exec(t_parse_list *parse_list, t_arg *arg)
{
    const char *path;
    char        *executable_path;

    path = get_path_from_envp(arg);
    executable_path = get_executable_path(parse_list->one_cmd->str, path);
    free((void*)path);
    if (!executable_path)
    {
       // printf("Commande introuvable : %s\n", command);
        exit(EXIT_FAILURE);
    }
    create_args(parse_list, arg);
    one_cmd(executable_path, parse_list, arg);
    free(executable_path);
    return (0);
}

static int one_cmd(const char *path, t_parse_list *parse_list, t_arg *arg) 
{
    pid_t pid;
    int status;
    int fd_in;
    int fd_out;
    //t_here_doc *here_doc;
    
    pid = fork();
    fd_in = STDIN_FILENO;
    fd_out = STDOUT_FILENO;
    //here_doc = open_heredoc(parse_list);
    if (pid == -1) 
    {
        perror("Erreur lors de la création du processus enfant");
        return (-1);
    } 
    else if (pid == 0)
    {
        handle_redirections(parse_list, &fd_in, &fd_out);
        exec_comd(path, arg, fd_in, fd_out);
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
        else 
        {
            printf("La commande ne s'est pas terminée normalement.\n");
            return (-1);
        }
    }
    return (0);
}

static void exec_comd(const char *path, t_arg *arg, int fd_in, int fd_out) 
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
            path = ft_strdup(arg->envp[i] + 5);
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