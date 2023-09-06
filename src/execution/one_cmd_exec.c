/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:57:21 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/06 17:35:45 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

static void handle_redirections(char **argv, int *fd_in, int *fd_out) 
{
    int i;

    i = 1;
    while (argv[i]) 
    {
        if (strcmp(argv[i], "<") == 0) 
        {
            *fd_in = open(argv[i + 1], O_RDONLY);
            if (*fd_in == -1) 
            {
                perror("Erreur lors de l'ouverture du fichier d'entrée");
                exit(1);
            }
            argv[i] = NULL;
            i++;
        } 
        else if (strcmp(argv[i], ">") == 0) 
        {
            *fd_out = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (*fd_out == -1) 
            {
                perror("Erreur lors de l'ouverture du fichier de sortie");
                exit(1);
            }
            argv[i] = NULL;
            i++;
        } 
        else 
            i++;
    }
}

static void exec_comd(const char *path, char **argv, char **envp, int fd_in, int fd_out) 
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
    execve(path, &argv[1], envp);
    perror("Erreur lors de l'exécution de la commande");
    exit(1);
}

int one_cmd_exec(const char *path, char **const argv, char **const envp) 
{
    pid_t pid;
    int status;
    int fd_in;
    int fd_out;
    char **res;

    pid = fork();
    fd_in = STDIN_FILENO;
    fd_out = STDOUT_FILENO;
    res = argv;
    if (pid == -1) 
    {
        perror("Erreur lors de la création du processus enfant");
        return (-1);
    } 
    else if (pid == 0)
    {
        handle_redirections(res, &fd_in, &fd_out);
        exec_comd(path, res, envp, fd_in, fd_out);
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

char **prepare_exec_args(int argc, char **argv, const char *executable_path)
{
    char **args;
    int i;
    
    args = (char **)malloc((argc + 1) * sizeof(char *));
    if (!args)
    {
        perror("Erreur lors de l'allocation de mémoire");
        free((void *)executable_path);
        exit(1);
    }
    i = 0;
    args[i] = (char *)executable_path;
    i++;
    while (i < argc)
    {
        args[i] = argv[i];
        i++;
    }
    args[argc] = NULL;
    //printf("args = %s", args[0]);
    return args;
}

void cmd_execution(t_parse_list *parse_list, t_env *env)
{
    if (is_builtin(parse_list->one_cmd))
        execute_builtin(parse_list->one_cmd, env);
    // else
    // {
    //     execute_multi_pipe();
    // }
}
