/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:08:13 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/14 20:12:59 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

static int wait_and_get_exit_status(pid_t pid);

static int execute_command(t_parse_list *parse_list, const char *path, t_arg *arg, int fd_in, int fd_out)
{
    pid_t pid;
    int status;

    pid = fork();
    
    if (pid == -1)
    {
        perror("Erreur lors de la création du processus enfant");
        return -1;
    }
    else if (pid == 0)
    {
        // Processus fils
        // Redirection d'entrée/sortie pour le fils
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
        create_args(parse_list, arg);
        exec_comds(path, arg);
        exit(EXIT_FAILURE); // En cas d'échec de l'exécution
    }
    else
    {
        // Processus parent
        status = wait_and_get_exit_status(pid);
        return status;
    }
}

static int wait_and_get_exit_status(pid_t pid)
{
    int status;

    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
    {
        return WEXITSTATUS(status);
    }
    else
    {
        printf("La commande ne s'est pas terminée normalement.\n");
        return -1;
    }
}

void exec_comds(const char *path, t_arg *arg)
{
    execve(path, arg->argv, arg->envp);
    perror("Erreur lors de l'exécution de la commande");
    exit(EXIT_FAILURE);
}

char *get_path_from_envp(t_arg *arg)
{
    int i = 0;

    while (arg->envp[i])
    {
        if (strncmp("PATH=", arg->envp[i], 5) == 0)
        {
            char *path = strdup(arg->envp[i] + 5);
            if (path == NULL)
            {
                perror("Erreur d'allocation de mémoire");
                exit(EXIT_FAILURE);
            }
            return path;
        }
        i++;
    }

    return NULL; // Si la variable PATH n'est pas trouvée
}

int multi_cmds_exec(t_parse_list *parse_list, t_arg *arg)
{
    const char *path;
    char *executable_path;

    path = get_path_from_envp(arg);
    int status = 0;
    int fd_in = STDIN_FILENO;
    int fd_out = STDOUT_FILENO;

    while (parse_list && path)
    {
        executable_path = get_executable_path(parse_list->one_cmd->str, path);
        printf("executable_path = %s\n", executable_path);

        if (!executable_path)
        {
            fprintf(stderr, "Commande introuvable : %s\n", parse_list->one_cmd->str);
            exit(EXIT_FAILURE);
        }

        handle_redirections(parse_list, &fd_in, &fd_out);
        // int i = 0;
        // while (arg->argv[i] != NULL)
        // {
        //     printf("arg->argv: %s\n", arg->argv[i]);
        //     i++;
        // }
        int cmd_status = execute_command(parse_list, executable_path, arg, fd_in, fd_out);
        if (cmd_status != 0)
        {
            fprintf(stderr, "La commande a échoué : %s\n", parse_list->one_cmd->str);
            status = -1; // Indique une erreur globale
        }

        free(executable_path);
        parse_list = parse_list->next;
    }

    return status;
}















































// static void exec_comds(const char *path, t_parse_list *parse_list, t_arg *arg, int fd_in, int fd_out)
// {
//     char **temp_argv;
//     int i;

//     if (fd_in != STDIN_FILENO)
//     {
//         dup2(fd_in, STDIN_FILENO);
//         close(fd_in);
//     }
//     if (fd_out != STDOUT_FILENO)
//     {
//         dup2(fd_out, STDOUT_FILENO);
//         close(fd_out);
//     }

//     // Allouez de la mémoire pour temp_argv et incluez un élément supplémentaire pour le NULL final.
//     temp_argv = malloc(sizeof(char *) * (arg->n_args + 2));
//     if (!temp_argv)
//     {
//         perror("Erreur lors de l'allocation de mémoire");
//         exit(EXIT_FAILURE);
//     }

//     // Copiez les arguments depuis arg->argv.
//     i = 0;
//     while (i < arg->n_args)
//     {
//         temp_argv[i] = strdup(arg->argv[i]);
//         if (!temp_argv[i])
//         {
//             perror("Erreur lors de l'allocation de mémoire");
//             exit(EXIT_FAILURE);
//         }
//         i++;
//     }

//     // Le dernier élément de temp_argv doit être NULL.
//     temp_argv[arg->n_args] = NULL;

//     handle_redirections(parse_list, &fd_in, &fd_out);

//     // Utilisez execve avec le chemin complet de l'exécutable.
//     execve(path, temp_argv, arg->envp);

//     // Gestion de l'échec de l'exécution de la commande
//     perror("Erreur lors de l'exécution de la commande");
//     exit(EXIT_FAILURE);
// }




// /*static int execute_command(const char *path, t_arg *arg, int fd_in, int fd_out, t_parse_list *parse_list)
// {
//     pid_t pid;
//     int status;

//     pid = fork();
//     if (pid == -1)
//     {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     else if (pid == 0) // Processus fils
//     {
//         // Redirection d'entrée
//         if (fd_in != STDIN_FILENO)
//         {
//             dup2(fd_in, STDIN_FILENO);
//             close(fd_in);
//         }

//         // Redirection de sortie
//         if (fd_out != STDOUT_FILENO)
//         {
//             dup2(fd_out, STDOUT_FILENO);
//             close(fd_out);
//         }
//         exec_comds(path, parse_list, arg, STDIN_FILENO, STDOUT_FILENO);
//         perror("Erreur lors de l'exécution de la commande");
//         exit(EXIT_FAILURE);
//     }
//     else // Processus parent
//     {
//         waitpid(pid, &status, 0);
//         if (WIFEXITED(status))
//         {
//             return WEXITSTATUS(status);
//         }
//         else
//         {
//             perror("La commande ne s'est pas terminée normalement.");
//             return -1;
//         }
//     }
// }*/

// // static void close_and_free_pipes(int **pipes, int num_pipes)
// // {
// //     for (int i = 0; i < num_pipes; i++)
// //     {
// //         close(pipes[i][0]);
// //         close(pipes[i][1]);
// //         free(pipes[i]);
// //     }
// //     free(pipes);
// // }

// static void execute_pipeline_recursive(t_parse_list *parse_list, t_arg *arg, int fd_in)
// {
//     int fd_out;
//     int pipe_fd[2];
//     pid_t pid;
//     int status;

//     if (parse_list == NULL)
//         return;

//     fd_out = STDOUT_FILENO;
//     if (parse_list->next != NULL)
//     {
//         if (pipe(pipe_fd) == -1)
//         {
//             perror("pipe");
//             exit(EXIT_FAILURE);
//         }
//         fd_out = pipe_fd[1];
//     }

//     // Appel de exec_comds pour chaque commande dans le pipeline
//     exec_comds(parse_list->one_cmd->str, parse_list, arg, fd_in, fd_out);

//     pid = fork();
//     if (pid == -1)
//     {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     else // Processus parent
//     {
//         waitpid(pid, &status, 0);
//         if (!WIFEXITED(status))
//         {
//             perror("La commande ne s'est pas terminée normalement.");
//             exit(EXIT_FAILURE);
//         }
//     }
//     if (fd_out != STDOUT_FILENO)
//         close(fd_out);

//     // Appel récursif pour le reste du pipeline
//     execute_pipeline_recursive(parse_list->next, arg, pipe_fd[0]);
// }


// static void execute_pipeline(t_parse_list *parse_list, t_arg *arg)
// {
//     execute_pipeline_recursive(parse_list, arg, STDIN_FILENO);
// }

// int multi_cmds_exec(t_parse_list *parse_list, t_arg *arg)
// {
//     const char *path;
//     char *executable_path;

//     path = get_path_from_envp(arg);
//     executable_path = get_executable_path(parse_list->one_cmd->str, path);
//     free((void *)path);
//     if (!executable_path)
//     {
//         perror("Commande introuvable");
//         return (-1);
//     }
//     create_args(parse_list, arg);
//     execute_pipeline(parse_list, arg);
//     free(executable_path);
//     return 0;
// }
//****************
// static pid_t exec_first_comd(t_parse_list *parse_list, t_arg *arg, int pipe_fd[2], int input_fd, t_env *env);
// static pid_t exec_second_comd(t_parse_list *parse_list, t_arg *arg, int pipe_fd[2], int output_fd, t_env *env);
// static int  wait_and_get_exit_status(pid_t pid);
// static pid_t exec_comd(t_parse_list *parse_list, t_arg *arg, t_env *env);

// int multi_cmds_exec(t_parse_list *parse_list, t_arg *arg, t_env *env)
// {
//     int pipe_fd[2];
//     int exit_status;
//     int fd_in;
//     int fd_out;

//     fd_in = STDIN_FILENO;
//     fd_out = STDOUT_FILENO;
//     if (pipe(pipe_fd) == -1) 
//     {
//         perror("Erreur lors de la création du tube");
//         return (-1);
//     }
//     pid_t pid1 = exec_first_comd(parse_list, arg, pipe_fd, fd_in, env);
//     close(pipe_fd[1]);
//     pid_t pid2 = exec_second_comd(parse_list, arg, pipe_fd, fd_out, env);
//     close(pipe_fd[0]);
//     wait_and_get_exit_status(pid1);
//     exit_status = wait_and_get_exit_status(pid2);
//     return (exit_status);
// }

// static int wait_and_get_exit_status(pid_t pid)
// {
//     int status;

//     waitpid(pid, &status, 0);
//     if (WIFEXITED(status))
//         return WEXITSTATUS(status);
//     else
//     {
//         printf("La commande ne s'est pas terminée normalement.\n");
//         return (-1);
//     }
// }

// static pid_t exec_comd(t_parse_list *parse_list, t_arg *arg, t_env *env) 
// {
//     char *path;
//     const char *executable_path;
//     path = get_path_from_envp(arg);
//     if (arg->argv && parse_list->one_cmd)
//     {
//         if (is_builtin(parse_list->one_cmd))
//             builtin_exec(parse_list->one_cmd, env, MULTI_CMD);
//         else
//         {
//             int i = 0;
//             while (i < arg->n_args)
//             {
//                 executable_path = get_executable_path(arg->argv[i], path);
//                 if (!executable_path) 
//                 {
//                     //perror("Commande introuvable");
//                     exit(1);
//                 }
//                 execve(executable_path, &arg->argv[i], arg->envp);
//                 i++;
//             }
//         }
//     }
//     perror("Erreur lors de l'exécution de la commande");
//     exit(1);
// }

// static pid_t exec_first_comd(t_parse_list *parse_list, t_arg *arg, int pipe_fd[2], int input_fd, t_env *env)
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
//         input_fd = open_input(parse_list->input, &input_fd);
//         if (input_fd == -1)
//         {
//             perror("Erreur lors de l'ouverture du fichier d'entrée");
//             exit(1);
//         }
//         create_args(parse_list, arg);
//         exec_comd(parse_list, arg, env);
//     }
//     return (pid1);
// }

// static pid_t exec_second_comd(t_parse_list *parse_list, t_arg *arg, int pipe_fd[2], int output_fd, t_env *env)
// {
//     pid_t pid2;
    
//     pid2 = fork();
//     if (pid2 == -1)
//     {
//         perror("Erreur lors de la création du processus enfant pour la deuxième commande");
//         exit(1);
//     }
//     else if (pid2 == 0)
//     {
//         close(pipe_fd[1]);
//         dup2(pipe_fd[0], STDIN_FILENO);
//         close(pipe_fd[0]);
//         output_fd = open_output(parse_list->output, &output_fd);
//         if (output_fd == -1)
//         {
//             perror("Erreur lors de l'ouverture du fichier de sortie");
//             exit(1);
//         }
//         create_args(parse_list, arg);
//         exec_comd(parse_list, arg, env);
//     }
//     return (pid2);
// }

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