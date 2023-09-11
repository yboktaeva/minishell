/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:58:28 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/11 18:28:52 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// static int unset_variable(char *name, t_env *env);
// static void	error_message(char *name);
// int str_check(char *str1, char *str2);

// int cmd_unset(t_one_cmd *one_cmd, t_env *env)
// {
//     int i;

//     i = 1;
//     while (i < arg->argc)
//     {
//         unset_variable(arg->argv[i], env);
//         i += 1;
//     }
//     return (EXIT_SUCCESS);
// }

// int cmd_unset(t_arg *arg, t_table *table)
// {
//     int i;

//     i = 1;
//     while (i < arg->argc)
//     {
//         unset_variable(arg->argv[i], table);
//         i += 1;
//     }
//     return (EXIT_SUCCESS);
// }

// static int unset_variable(char *name, t_env *env)
// {
//     t_env *tmp;
//     t_env *temp;
//     t_env *prev_node = NULL;

//     tmp = env;
//     if (ft_strchr(name, '='))
//     {
//         error_message(name);
//         return (EXIT_FAILURE);
//     }
//     temp = env->next;
//     while (temp != NULL)
//     {
//         printf("%s=%s\n", temp->var_name, temp->var_value);
//         temp = temp->next;
//     }
//     while (tmp)
//     {
//         printf("name :%s\n tmp->var_name: %s\n", name, tmp->var_name);
//         if (str_check(name, tmp->var_name))
//         {
//             printf("name :%s\n tmp->var_name: %s\n", name, tmp->var_name);
//             if (prev_node)
//                 prev_node->next = tmp->next;
//             else
//                 tmp = tmp->next;
//             free(tmp->var_name);
//             free(tmp->var_value);
//             free(tmp);
//             return (EXIT_SUCCESS);
//         }
//         prev_node = tmp;
//         tmp = tmp->next;
//     }
//     return (EXIT_SUCCESS); // Variable non trouvée, pas d'erreur
// }

// static void	error_message(char *name)
// {
// 	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
// 	ft_putstr_fd(name, STDERR_FILENO);
// 	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
// }

// int str_check(char *str1, char *str2)
// {
//     if (!str1 || !str2)
//         return 0;

//     while (*str1 && *str2)
//     {
//         if (*str1 != *str2)
//             return 0;
//         str1++;
//         str2++;
//     }
//     return (*str1 == '\0' && *str2 == '\0');
// }

/*int	str_check(char *str1, char *str2)
{
	size_t	i;

	if ((str1 && !str2) || (!str1 && str2))
		return (0);
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i += 1;
	}
	return (1);
}*/


/*static int unset_variable(char *name, t_table *table)
{
    t_env *tmp;
    t_env *next_node;

    tmp = table->env;
    if (ft_strchr(name, '='))
    {
        error_message(name);
        return (EXIT_FAILURE);
    }
    while (tmp && tmp->next != NULL)
    {
        if (str_check(name, tmp->next->var_name))
        {
            next_node = tmp->next->next;
            free(tmp->next->var_name);
            free(tmp->next->var_value);
            free(tmp->next);
            tmp->next = next_node;
            break;
        }
        tmp = tmp->next;
    }
    return (EXIT_SUCCESS);
}*/

