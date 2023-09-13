/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_cmds_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:35:47 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/13 20:08:32 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

static pid_t exec_first_comd(t_parse_list *parse_list, t_arg *arg, int pipe_fd[2], int input_fd);
static pid_t exec_second_comd(t_parse_list *parse_list, t_arg *arg, int pipe_fd[2], int output_fd);
static int wait_and_get_exit_status(pid_t pid);
static pid_t exec_comd(t_parse_list *parse_list, t_arg *arg);

int two_cmds_exec(t_parse_list *parse_list, t_arg *arg)
{
    int pipe_fd[2];
    int exit_status;
    int fd_in;
    int fd_out;

    fd_in = STDIN_FILENO;
    fd_out = STDOUT_FILENO;
    if (pipe(pipe_fd) == -1) 
    {
        perror("Erreur lors de la création du tube");
        return (-1);
    }
    pid_t pid1 = exec_first_comd(parse_list, arg, pipe_fd, fd_in);
    close(pipe_fd[1]);
    pid_t pid2 = exec_second_comd(parse_list, arg, pipe_fd, fd_out);
    close(pipe_fd[0]);
    wait_and_get_exit_status(pid1);
    exit_status = wait_and_get_exit_status(pid2);
    return (exit_status);
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

static pid_t exec_comd(t_parse_list *parse_list, t_arg *arg) 
{
    const char *path;
    const char *executable_path;
    path = get_path_from_envp(arg);
    executable_path = get_executable_path(parse_list->one_cmd->str, path);
    if (!executable_path) 
    {
        //perror("Commande introuvable");
        exit(1);
    }
    init_args(parse_list, arg);
    execve(executable_path, arg->argv, arg->envp);
    perror("Erreur lors de l'exécution de la commande");
    exit(1);
}


static pid_t exec_first_comd(t_parse_list *parse_list, t_arg *arg, int pipe_fd[2], int input_fd)
{
    pid_t pid1;
    
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("Erreur lors de la création du processus enfant pour la première commande");
        exit(1);
    }
    else if (pid1 == 0)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        input_fd = open_input(parse_list->input, &input_fd);
        if (input_fd == -1)
        {
            perror("Erreur lors de l'ouverture du fichier d'entrée");
            exit(1);
        }
        // dup2(input_fd, STDIN_FILENO);
        // close(input_fd);
        exec_comd(parse_list, arg);
    }
    return (pid1);
}

static pid_t exec_second_comd(t_parse_list *parse_list, t_arg *arg, int pipe_fd[2], int output_fd)
{
    pid_t pid2;
    
    pid2 = fork();
    if (pid2 == -1)
    {
        perror("Erreur lors de la création du processus enfant pour la deuxième commande");
        exit(1);
    }
    else if (pid2 == 0)
    {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        output_fd = open_output(parse_list->output, &output_fd);
        if (output_fd == -1)
        {
            perror("Erreur lors de l'ouverture du fichier de sortie");
            exit(1);
        }
        // dup2(output_fd, STDOUT_FILENO);
        // close(output_fd);
        exec_comd(parse_list, arg);
    }
    return (pid2);
}

/*int create_pipe(int pipe_fd[2]) 
{
    if (pipe(pipe_fd) == -1) 
    {
        perror("Erreur lors de la création du tube");
        return (-1);
    }
    return (0);
}*/



// // Compte le nombre d'arguments dans un tableau de chaînes jusqu'à rencontrer NULL.
// static int count_args(char **args) 
// {
//     int count = 0;
//     while (*args != NULL) 
//     {
//         ++count;
//         ++args;
//     }
//     return (count);
// }

// // Alloue et remplit un tableau d'arguments avec l'exécutable et les arguments donnés.
// static char **create_tab_of_args(const char *executable, const char *cmd, char **envp) 
// {
//     int count = count_args(envp) + 2; // cmd et NULL
//     char **args = (char **)malloc(count * sizeof(char *));
//     if (!args) 
//     {
//         perror("Erreur d'allocation mémoire");
//         exit(1);
//     }
//     args[0] = (char *)executable;
//     args[1] = (char *)cmd;
    
//     int i = 2;
//     char **env = envp;
//     while (*env != NULL) 
//     {
//         args[i] = *env;
//         ++i;
//         ++env;
//     }
//     args[count - 1] = NULL;
//     return (args);
// }

// // Exécute une commande avec les arguments fournis.
// static pid_t exec_comd(const char *cmd, char **const envp) 
// {
//     const char *path;
//     const char *executable_path;

//     path = getenv("PATH");
//     executable_path = get_executable_path(cmd, path);
//     if (!executable_path) 
//     {
//         perror("Commande introuvable");
//         exit(1);
//     }
    
//     char **args = create_tab_of_args(executable_path, cmd, envp);
//     execve(executable_path, args, envp);
//     perror("Erreur lors de l'exécution de la commande");
//     exit(1);
// }

// Exécute une commande avec les arguments fournis.

// static pid_t exec_first_comd(const char *cmd1, char **const envp, int pipe_fd[2], const char *input_file)
// {
//     pid_t pid1;

//     pid1 = fork();
//     if (pid1 == -1)
//     {
//         perror("Erreur lors de la création du processus enfant pour la première commande");
//         exit(1);
//     }
//     else if (pid1 == 0)
//     {
//         close(pipe_fd[0]);
//         dup2(pipe_fd[1], STDOUT_FILENO);
//         close(pipe_fd[1]);
//         int input_fd = open(input_file, O_RDONLY);
//         if (input_fd == -1)
//         {
//             perror("Erreur lors de l'ouverture du fichier d'entrée");
//             exit(1);
//         }
//         dup2(input_fd, STDIN_FILENO);
//         close(input_fd);
//         exec_comd(cmd1, envp);
//     }
//     return (pid1);
// }



/*int two_cmds_exec(const char *cmd1, const char *cmd2, char **const envp)
{
    int pipe_fd[2];
    int exit_status;

    if (pipe(pipe_fd) == -1) 
    {
        perror("Erreur lors de la création du tube");
        return (-1);
    }
    //printf("je suis dans two_cmds_exec apres pipe");
    pid_t pid1 = exec_first_comd(cmd1, envp, pipe_fd);
    close(pipe_fd[1]);
    pid_t pid2 = exec_second_comd(cmd2, envp, pipe_fd);
    close(pipe_fd[0]);
    wait_and_get_exit_status(pid1);
    exit_status = wait_and_get_exit_status(pid2);
    return (exit_status);
}*/