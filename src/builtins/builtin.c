/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:21:40 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/11 23:54:41 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"

int g_status;

int is_builtin(t_one_cmd *one_cmd)
{
    if (one_cmd == NULL)
        return (0);
    if (ft_strncmp(one_cmd->str, "echo", 5) == 0)
        return (1);
    else if (ft_strncmp(one_cmd->str, "cd", 3) == 0)
        return (1);
    else if (ft_strncmp(one_cmd->str, "pwd", 4) == 0)
        return (1);
    else if (ft_strncmp(one_cmd->str, "export", 7) == 0)
        return (1);
    else if (ft_strncmp(one_cmd->str, "unset", 6) == 0)
        return (1);
    else if (ft_strncmp(one_cmd->str, "env", 4) == 0)
        return (1);
    else if (ft_strncmp(one_cmd->str, "exit", 5) == 0)
        return (1);
    return (0);
}

void    execute_builtin(t_one_cmd *one_cmd, t_env *env)
{
    int builtin_status;
    
    builtin_status = 0;
    if (ft_strncmp(one_cmd->str, "echo", 5) == 0)
        builtin_status = cmd_echo(one_cmd);
    // else if (ft_strncmp(one_cmd->str, "cd", 3) == 0)
    //     builtin_status = cmd_cd(one_cmd, env);
    else if (ft_strncmp(one_cmd->str, "pwd", 4) == 0)
        builtin_status = cmd_pwd(one_cmd);
    // else if (ft_strncmp(one_cmd->str, "export", 7) == 0)
    //     builtin_status = cmd_export(one_cmd, env);
    // else if (ft_strncmp(one_cmd->str, "unset", 6) == 0)
    //     builtin_status = cmd_unset(one_cmd, env);
    else if (ft_strncmp(one_cmd->str, "env", 4) == 0)
        builtin_status = cmd_env(env);
    // else if (ft_strncmp(one_cmd->str, "exit", 5) == 0)
    //     builtin_status = cmd_exit(one_cmd, env);
    g_status = builtin_status;
    return ;
}