/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:57:21 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/11 21:13:20 by yuboktae         ###   ########.fr       */
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

static void handle_redirections(t_parse_list *parse_list, int *fd_in, int *fd_out);
static int one_cmd(const char *path, t_parse_list *s, t_arg *arg);
static void exec_comd(const char *path, t_parse_list *s, t_arg *arg, int fd_in, int fd_out);
int one_cmd_exec(t_parse_list *s, t_arg *arg);
char    *get_path_from_envp(t_arg *arg);


void cmd_execution(t_parse_list *parse_list, t_env *env, t_arg *arg)
{
    int n_cmd;

    n_cmd = cmd_size(parse_list);
    if (n_cmd == 1 && is_builtin(parse_list->one_cmd))
        execute_builtin(parse_list->one_cmd, env);
    else if (n_cmd == 1)
        one_cmd_exec(parse_list, arg);
    // else
    // {
    //     execute_multi_pipe();
    // }
    return ;
}

int one_cmd_exec(t_parse_list *s, t_arg *arg)
{
    const char *path;
    char *executable_path;
    //char **args;
    //int exit_code;

    // if (argc < 2)
    // {
    //     printf("Usage: %s commande [arguments...]\n", argv[0]);
    //     return 1;
    // }
   // command = argv[1];
    //exit_code = 0;
    path = get_path_from_envp(arg);
    executable_path = get_executable_path(s->one_cmd->str, path);
    if (!executable_path)
    {
       // printf("Commande introuvable : %s\n", command);
        exit(EXIT_FAILURE);
    }
    //args = prepare_exec_args(argc, argv, executable_path);
    one_cmd(executable_path, s, arg);
    free((void *)executable_path);
    //free(args);
    //if (exit_code == -1)
     //   printf("L'exécution de la commande a échoué.\n");
    //else
      //  printf("La commande s'est terminée avec le code de sortie : %d\n", exit_code);
    return 0;
}

static int one_cmd(const char *path, t_parse_list *parse_list, t_arg *arg) 
{
    pid_t pid;
    int status;
    int fd_in;
    int fd_out;
    //char **res;

    pid = fork();
    fd_in = STDIN_FILENO;
    fd_out = STDOUT_FILENO;
    //res = argv;
    if (pid == -1) 
    {
        perror("Erreur lors de la création du processus enfant");
        return (-1);
    } 
    else if (pid == 0)
    {
        handle_redirections(parse_list, &fd_in, &fd_out);
        exec_comd(path, parse_list, arg, fd_in, fd_out);
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

static void exec_comd(const char *path, t_parse_list *s, t_arg *arg, int fd_in, int fd_out) 
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
    execve(path, &s->one_cmd, arg->envp);
    perror("Erreur lors de l'exécution de la commande");
    exit(1);
}

char    *get_path_from_envp(t_arg *arg)
{
    char    *path;
    char    **tmp;
   
    path = NULL;
    tmp = arg->envp;
    
    while (*tmp)
    {
        if (ft_strncmp(*tmp, "PATH=", 5) == 0)
        {
            path = ft_strdup(*tmp + 5);
            if (path == NULL)
            {
                perror("Erreur d'allocation de mémoire");
                exit(EXIT_FAILURE);
            }
            break;
        }
        tmp++;
    }
    return (path);
}

static void handle_redirections(t_parse_list *parse_list, int *fd_in, int *fd_out) 
{
    t_parse_list    *tmp;

    tmp = parse_list;
    while (tmp->next != NULL) 
    {
        if (tmp->input) 
        {
            *fd_in = open(tmp->input->file_name, O_RDONLY);
            if (*fd_in == -1) 
            {
                perror("Erreur lors de l'ouverture du fichier d'entrée");
                exit(1);
            }
            //argv[i] = NULL;
            tmp = tmp->next;
        } 
        else if (tmp->output)
        {
            *fd_out = open(tmp->output->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (*fd_out == -1) 
            {
                perror("Erreur lors de l'ouverture du fichier de sortie");
                exit(1);
            }
            //argv[i] = NULL;
            tmp = tmp->next;
        } 
        else 
            tmp = tmp->next;
    }
}
