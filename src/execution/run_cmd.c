/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:06:08 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/09/21 17:48:35 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include "utils.h"

void cmd_execution(t_parse_list *parse_list, t_table *info, t_env *env, t_arg *arg)
{
    int n_cmd;
    
    (void)info;
    n_cmd = cmd_size(parse_list);
    if (n_cmd == 1)
    {
        if (is_builtin(parse_list->one_cmd))
            one_builtin(parse_list, env);
        else
            one_cmd_exec(parse_list, arg, env);
    }
    // else
    // {
    //     multi_cmds_exec(parse_list, arg, env);
    // }
    return ;
}

void    one_builtin(t_parse_list *parse_list, t_env *env)
{
    /*init parent redir*/
    builtin_exec(parse_list->one_cmd, env, ONE_CMD);
}
