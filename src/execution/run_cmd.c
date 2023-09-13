/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:06:08 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/09/14 00:29:42 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

void cmd_execution(t_parse_list *parse_list, t_env *env, t_arg *arg)
{
    int n_cmd;

    n_cmd = cmd_size(parse_list);
    if (n_cmd == 1)
    {
        if (is_builtin(parse_list->one_cmd))
            one_builtin(parse_list->one_cmd, env);
        else
            one_cmd_exec(parse_list, arg);
    }
    else
        two_cmds_exec(parse_list, arg);
    return ;
}

void    one_builtin(t_parse_list *parse_list, t_env *env)
{
    /*init parent redir*/
    builtin_exec(parse_list->one_cmd, env, ONE_CMD);
}
