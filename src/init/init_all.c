/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:57:27 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/09/25 17:09:53 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

//static t_cmd_info *init_cmd_info();

void *init_main_table(t_table *main, char *line, char **envp)
{
    (void)line;
    (void)envp;
    //init_execve_args(&arg, envp);
    // t_token tokens;
    // info->cmds =;
    main->cmd_count = 0;
    //main->cmd_info = init_cmd_info();
    return (SUCCES);
}

// static t_cmd_info *init_cmd_info()
// {
//     t_cmd_info *cmd_info;
    
//     cmd_info = NULL;
//     cmd_info = malloc(sizeof(t_cmd_info));
//     cmd_info->fd = malloc(sizeof(int) * 2);
//     cmd_info->fd[0] = -1;
//     cmd_info->fd[1] = -1;
//     return (cmd_info);
// }

void    *init_execve_args(t_arg *arg, t_env *env)
{
    arg->envp = NULL;
    arg->envp = duplicate_envp(env);
    return (SUCCES);
}

t_parse_list *init_parse_list(void)
{
    t_parse_list    *new;

    new = malloc(sizeof(t_parse_list));
    if (!new)
        return (NULL);
    new->one_cmd = NULL;
    new->input = NULL;
    new->output = NULL;
    new->next = NULL;
    return (new);
}

t_one_cmd   *init_one_cmd(char *str)
{
    t_one_cmd   *new;

    new = malloc(sizeof(t_one_cmd));
    if (!new)
        return (NULL);
    new->str = str;
    new->next = NULL;
    return (new);
}

t_redir *init_redir_list(t_type type, char *name)
{
    t_redir *new;

    new = malloc(sizeof(t_redir));
    if (!new)
        return (new);
    new->type = type;
    new->file_name = name;
    new->next = NULL;
    return (new);
}