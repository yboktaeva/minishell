/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:08:13 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/20 20:31:29 by yuboktae         ###   ########.fr       */
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

// static int wait_and_get_exit_status(pid_t pid);

// static int *execute_command(t_parse_list *parse_list, const char *path, t_arg *arg, int *fd, int nb, int out, int nb_cmd)
// {
//     int res;
//     int *fdc;
//     pid_t pid;
   
//     create_args(parse_list, arg);
//     res = -1;
//     fdc = malloc(sizeof(int) * 2);
//     res = pipe(fdc);
//     if (res == -1)
//         exit(-1);
//     pid = fork();
//     if (pid == -1)
//     {
//         perror("Erreur lors de la création du processus enfant");
//         return (NULL);
//     }
//     else if (pid == 0)
//     {
//         dup2(fd[0], STDIN_FILENO);
//         close(fd[1]);
//         close(fd[0]);
//         if(out != STDOUT_FILENO)
//             dup2(out, STDOUT_FILENO);
//         else if(nb != nb_cmd)
//             dup2(fdc[1], STDOUT_FILENO);
//         exec_comds(path, arg);
//         exit(EXIT_FAILURE);
//     }
//     else
//     {
//         close(fd[0]);
//         close(fd[1]);
//         wait_and_get_exit_status(pid);
//         return (fdc);
//     }
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
//         return -1;
//     }
// }

// void exec_comds(const char *path, t_arg *arg)
// {
//     execve(path, arg->argv, arg->envp);
//     perror("Erreur lors de l'exécution de la commande");
//     exit(EXIT_FAILURE);
// }

// char *get_path_from_envp(t_arg *arg)
// {
//     int i = 0;

//     while (arg->envp[i])
//     {
//         if (strncmp("PATH=", arg->envp[i], 5) == 0)
//         {
//             char *path = strdup(arg->envp[i] + 5);
//             if (path == NULL)
//             {
//                 perror("Erreur d'allocation de mémoire");
//                 exit(EXIT_FAILURE);
//             }
//             return path;
//         }
//         i++;
//     }
//     return (NULL);
// }

// int multi_cmds_exec(t_parse_list *parse_list, t_arg *arg)
// {
//     const char *path;
//     char *executable_path;
//     int status;
//     int res;
//     int *fd;
//     int out;
//     int nb_cmd;
//     int i;

//     path = get_path_from_envp(arg);
//     status = 0;
//     res = -1;
//     fd = malloc(sizeof(int) * 2);
//     res = pipe(fd);
//     if (res == -1)
//         exit(-1);
//     i = 1;
//     nb_cmd = cmd_size(parse_list);
//     while (parse_list && path)
//     {
//         out = STDOUT_FILENO;
//         executable_path = get_executable_path(parse_list->one_cmd->str, path);
//         if (!executable_path)
//         {
//             fprintf(stderr, "Commande introuvable : %s\n", parse_list->one_cmd->str);
//             exit(EXIT_FAILURE);
//         }
//         handle_redirections(parse_list, &fd[0], &out);
//         fd = execute_command(parse_list, executable_path, arg, fd, i, out, nb_cmd);
//         free(executable_path);
//         parse_list = parse_list->next;
//         i++;
//     }
//     return (status);
// }




// static int wait_and_get_exit_status(pid_t pid);

// static int *execute_command(t_parse_list *parse_list, const char *path, t_arg *arg, int *fd, int nb, int out, int nb_cmd)
// {
//     int res;
//     int *fdc;
//     pid_t pid;
   
//     create_args(parse_list, arg);
//     res = -1;
//     fdc = malloc(sizeof(int) * 2);
//     res = pipe(fdc);
//     if (res == -1)
//         exit(-1);
//     pid = fork();
//     if (pid == -1)
//     {
//         perror("Erreur lors de la création du processus enfant");
//         return (NULL);
//     }
//     else if (pid == 0)
//     {
//         dup2(fd[0], STDIN_FILENO);
//         close(fd[1]);
//         close(fd[0]);
//         if(out != STDOUT_FILENO)
//             dup2(out, STDOUT_FILENO);
//         else if(nb != nb_cmd)
//             dup2(fdc[1], STDOUT_FILENO);
//         exec_comds(path, arg);
//         exit(EXIT_FAILURE);
//     }
//     wait_and_get_exit_status(pid);
//     close(fd[0]);
//     close(fd[1]);
//     return (fdc);
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
//         return -1;
//     }
// }

// void exec_comds(const char *path, t_arg *arg)
// {
//     execve(path, arg->argv, arg->envp);
//     perror("Erreur lors de l'exécution de la commande");
//     exit(EXIT_FAILURE);
// }

// char *get_path_from_envp(t_arg *arg)
// {
//     int i = 0;

//     while (arg->envp[i])
//     {
//         if (strncmp("PATH=", arg->envp[i], 5) == 0)
//         {
//             char *path = strdup(arg->envp[i] + 5);
//             if (path == NULL)
//             {
//                 perror("Erreur d'allocation de mémoire");
//                 exit(EXIT_FAILURE);
//             }
//             return path;
//         }
//         i++;
//     }
//     return (NULL);
// }

// int multi_cmds_exec(t_parse_list *parse_list, t_arg *arg)
// {
//     const char *path;
//     char *executable_path;
//     int status;
//     int res;
//     int *fd;
//     int out;
//     int nb_cmd;
//     int i;

//     path = get_path_from_envp(arg);
//     status = 0;
//     res = -1;
//     fd = malloc(sizeof(int) * 2);
//     res = pipe(fd);
//     if (res == -1)
//         exit(-1);
//     i = 1;
//     nb_cmd = cmd_size(parse_list);
//     while (parse_list && path)
//     {
//         out = STDOUT_FILENO;
//         executable_path = get_executable_path(parse_list->one_cmd->str, path);
//         if (!executable_path)
//         {
//             fprintf(stderr, "Commande introuvable : %s\n", parse_list->one_cmd->str);
//             exit(EXIT_FAILURE);
//         }
//         handle_redirections(parse_list, &fd[0], &out);
//         fd = execute_command(parse_list, executable_path, arg, fd, i, out, nb_cmd);
//         free(executable_path);
//         parse_list = parse_list->next;
//         i++;
//     }
//     return (status);
// }