/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:06:08 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/09/20 19:27:46 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include "utils.h"

void cmd_execution(t_parse_list *parse_list, t_table *info, t_env *env, t_arg *arg)
{
    int n_cmd;

    n_cmd = cmd_size(parse_list);
    if (n_cmd == 1)
    {
        if (is_builtin(parse_list->one_cmd))
            one_builtin(parse_list, info, env);
        else
            one_cmd_exec(parse_list, arg);
    }
    // else
    // {
    //     multi_cmds_exec(parse_list, arg, env);
    // }
    return ;
}

void    one_builtin(t_parse_list *parse_list, t_table *info, t_env *env)
{
    /*init parent redir*/
    builtin_exec(parse_list->one_cmd, env, info, ONE_CMD);
}
