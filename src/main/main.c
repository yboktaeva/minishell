/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:32:14 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/01 15:25:22 by yuboktae         ###   ########.fr       */
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

// static int	word_count(char const *s, char c)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == c && s[i])
// 			i++;
// 		if (s[i] != c && s[i])
// 			count++;
// 		while (s[i] != c && s[i])
// 			i++;
// 	}
// 	return (count);
// }

// static void	free_words(char **tab, int i)
// {
// 	while (i > 0)
// 	{
// 		free (tab[i - 1]);
// 		i--;
// 	}
// 	free (tab);
// }

/*int main(int argc, char **argv, char **const envp)
{
    (void)argc;
    (void)argv;
    char *buffer;
    char **cmd;
    size_t buf_size;
    size_t len;
    t_table info;
    int i;

    i = 0;
    while (envp[i])
        i++;
    info.envp = (char **)malloc((i + 1) * sizeof(char *));
    if (!info.envp)
    {
        perror("Malloc failure");
        return (EXIT_FAILURE);
    }
    ft_memcpy(info.envp, envp, (i + 1) * sizeof(char *));
    pwd_oldpwd(&info);
    write(1, "$> ", 3);

    buffer = NULL;
    buf_size = 2048;
    cmd = NULL;
    buffer = (char *)calloc(sizeof(char), buf_size);
    if (buffer == NULL)
    {
        perror("Malloc failure");
        return (EXIT_FAILURE);
    }
    while (getline(&buffer, &buf_size, stdin) > 0)
    {
        len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
        cmd = ft_split(buffer, ' ');
        if (cmd[0] == NULL)
            printf("Command not found\n");
        else if (strcmp(cmd[0], "cd") == 0)
        {
            char *arg = (cmd[1] != NULL) ? cmd[1] : NULL;
            printf("Value of PWD: %s\n", print_path("PWD", info.envp));
            printf("Value of OLDPWD: %s\n", print_path("OLDPWD", info.envp));
            cmd_cd(&info, arg);
            printf("Value of PWD: %s\n", print_path("PWD", info.envp));
            printf("Value of OLDPWD: %s\n", print_path("OLDPWD", info.envp));
        }
        else
        {
            printf("Command: %s\n", cmd[0]);
            printf("Command must be : cd\n");
            break;
        }
        write(1, "$> ", 3);
        free_words(cmd, word_count(buffer, ' '));
    }
    free(cmd);
    free(buffer);
    free(info.envp);
    free(info.pwd);
    free(info.old_pwd);
    return 0;
}*/

/*int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_table info;

    info.env = init_env_list(envp);
    cmd_env(&info);
    free_env(&info.env);
    return (0);
}*/

/*int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_table info;

    info.env = init_env_list(envp);
    cmd_pwd();
    free_env(&info.env);
    return (0);
}*/

// int main(int argc, char **argv)
// {
//     (void)argc;
//     (void)argv;
//     char *buffer;
//     char **cmd;
//     t_table info;
//     size_t buf_size;
//     size_t len;

//     buffer = NULL;
//     buf_size = 2048;
//     write(1, "$> ", 3);
//     buffer = (char *)calloc(sizeof(char), buf_size);
//     if (buffer == NULL)
//     {
//         perror("Malloc failure");
//         return (EXIT_FAILURE);
//     }
//     cmd = NULL;
//     while (getline(&buffer, &buf_size, stdin) > 0)
//     {
//         len = strlen(buffer);
//         if (len > 0 && buffer[len - 1] == '\n')
//             buffer[len - 1] = '\0';
//         cmd = ft_split(buffer, ' ');
//         if (cmd[0] == NULL)
//             printf("Command not found\n");
//         else if (strcmp(cmd[0], "echo") == 0)
//             cmd_echo(&info, cmd);
//         else
//         {
//             printf("Command must be : echo\n");
//             break;
//         }
//         write(1, "$> ", 3);
//         free_words(cmd, word_count(buffer, ' '));
//     }
//     free(cmd);
//     free(buffer);
//     return 0;
// }

