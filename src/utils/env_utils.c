/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:53:58 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/29 19:09:22 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char    *env_key(char *str)
{
    char *key;

    key = ft_substr(str, 0, env_key_len);
    return (key);
}

int	env_key_len(char *key)
{
	int	i;

	i = 0;
	if (*key == '?' || ft_isdigit(*key))
		return (1);
	while (key[i] == '_'|| ft_isalpha(key[i]) || ft_isdigit(key[i]))
		i++;
	return (i);
}

char    *env_value(t_env *head, char *key)
{
    t_env   *env;
    int key_len;

    env = head;
    key_len = ft_strlen(key);
    // if (*key == '?')
    // {
    //      return (ft_itoa(info->exit_status));
    // }
    while (env->next)
    {
        if (ft_strncmp(key, env->key, key_len + 1) == 0)
        {
            if (env->value == NULL)
                return (ft_strdup(""));
            return (ft_strdup(env->value));
        }
        env = env->next;
    }
    return (ft_strdup(""));
}

void    print_env_list(t_env *env)
{
    t_env *head;
    
    head = env;
    while (head->next != NULL)
    {
        if (head->value != NULL)
            printf("%s=%s\n", head->key, head->value);
        head = head->next;
    }
}

// int     env_size(t_env *env)
// {
//     t_env   *tmp;
//     int     len;

//     len = 0;
//     tmp = env;
//     while (tmp != NULL)
//     {
//         len++;
//         tmp = tmp->next;
//     }
//     return (len);
// }

// t_env   *get_last(t_env *env)
// {
//     if (!env)
//         return (NULL);
//     while (env->next != NULL)
//         env = env->next;
//     return (env);
// }