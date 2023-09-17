/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:10:16 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/17 18:11:53 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int cmd_env(t_env *env)
{
    print_env_list(env);
    return (0);
}
