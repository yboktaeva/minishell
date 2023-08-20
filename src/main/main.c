/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:32:14 by asekmani          #+#    #+#             */
/*   Updated: 2023/08/16 17:37:56 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// int main(int arc, char **arv)
// {
//     const char *command = arv[1];
//     const char *path = getenv("PATH");
//     char *executable_path = get_executable_path(command, path);

//     if (arc != 2)
//     {
//         printf("Utilisation : %s <commande>\n", arv[0]);
//         return 1;
//     }
//     if (executable_path)
//     {
//         printf("Executable PATH for %s => : %s\n", command, executable_path);
//         free(executable_path);
//     }
//     else
//         printf("Unable to find Executable PATH for => %s\n", command);
//     return 0;
// }

/*int main(int argc, char **argv, char **const envp)
{
    const char *command;
    const char *path;
    char *executable_path;
    char **args;
    //int exit_code;

    if (argc < 2)
    {
        printf("Usage: %s commande [arguments...]\n", argv[0]);
        return 1;
    }
    command = argv[1];
    //exit_code = 0;
    path = getenv("PATH");
    executable_path = get_executable_path(command, path);
    if (!executable_path)
    {
        printf("Commande introuvable : %s\n", command);
        return (1);
    }
    args = prepare_exec_args(argc, argv, executable_path);
    one_cmd_exec(executable_path, args, envp);
    free((void *)executable_path);
    free(args);
    //if (exit_code == -1)
     //   printf("L'exécution de la commande a échoué.\n");
    //else
      //  printf("La commande s'est terminée avec le code de sortie : %d\n", exit_code);
    return 0;
}*/

/*int main(int argc, char **argv, char **const envp)
{
    const char *cmd1;
    const char *cmd2;
    const char *input_file;
    const char *output_file;
    int exit_code;

    if (argc < 5)
    {
        printf("Usage: %s input_file.txt commande1 commande2 output_file.txt\n", argv[0]);
        return 1;
    }

    input_file = argv[1];
    cmd1 = argv[2];
    cmd2 = argv[3];
    output_file = argv[4];

    exit_code = two_cmds_exec(cmd1, cmd2, envp, input_file, output_file);
    if (exit_code == -1)
        printf("L'exécution des commandes a échoué.\n");
    else
        printf("Les commandes se sont terminées avec le code de sortie : %d\n", exit_code);
    
    return 0;
}*/