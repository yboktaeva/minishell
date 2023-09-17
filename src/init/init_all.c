/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:57:27 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/09/17 18:25:52 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

void *init_main_table(t_table *info, char *line, char **envp)
{
    (void)line;
    (void)envp;
    //init_execve_args(&arg, envp);
    // t_token tokens;
    // info->cmds =;
    // info->path = get_executable_path(info->env);
    info->cmd_count = 0;
    return (SUCCES);
}

void    *init_execve_args(t_arg *arg, t_env *env)
{
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