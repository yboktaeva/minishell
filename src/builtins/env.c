/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:10:16 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/07 11:30:23 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

// int cmd_env(t_table *info)
// {
//     t_env *temp = info->env;

//     while (temp != NULL)
//     {
//         printf("%s=%s\n", temp->var_name, temp->var_value);
//         temp = temp->next;
//     }
//     free_env(&temp);
//     return (EXIT_SUCCESS);
// }

int cmd_env(t_env *env)
{
    print_env_list(env);
    return (0);
}
