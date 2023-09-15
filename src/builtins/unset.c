/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:58:28 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/15 18:15:41 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
# include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int unset_variable(char *name, t_env *env);
static void	error_message(char *name);
int str_check(char *str1, char *str2);

int cmd_unset(t_one_cmd *one_cmd, t_env *env)
{
    while (one_cmd)
    {
        unset_variable(one_cmd->str, env);
        one_cmd = one_cmd->next;
    }
    return (0);
}

static int unset_variable(char *name, t_env *env)
{
    t_env *tmp;
    t_env *temp;
    t_env *prev_node = NULL;

    tmp = env;
    if (ft_strchr(name, '='))
    {
        error_message(name);
        return (1);
    }
    temp = env->next;
    while (temp != NULL)
        temp = temp->next;
    while (tmp)
    {
        if (str_check(name, tmp->var_name))
        {
            if (prev_node)
                prev_node->next = tmp->next;
            else
                tmp = tmp->next;
            free(tmp->var_name);
            free(tmp->var_value);
            free(tmp);
            return (0);
        }
        prev_node = tmp;
        tmp = tmp->next;
    }
    return (0);
}

static void	error_message(char *name)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
}
