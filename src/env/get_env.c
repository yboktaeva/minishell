/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:08:15 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/25 17:53:04 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

t_env   *create_env(char *key, char *value)
{
    t_env  *new;

    new = malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->key = key;
    new->value = value;
    new->next = NULL;
    return (new);
}

t_env   *get_last(t_env *env)
{
    if (!env)
        return (NULL);
    while (env->next != NULL)
        env = env->next;
    return (env);
}

void    env_add_back(t_env **env, t_env *new)
{
    t_env   *tmp;

    if (new == NULL)
        return ;
    tmp = *env;
    if (!tmp)
    {
        *env = new;
        return ;
    }
    tmp = get_last(tmp);
    tmp->next = new;
}

int     env_size(t_env *env)
{
    t_env   *tmp;
    int     len;

    len = 0;
    tmp = env;
    while (tmp != NULL)
    {
        len++;
        tmp = tmp->next;
    }
    return (len);
}

t_env	*get_env(char **envp)
{
    t_env   *head;
    t_env   *new;
    char    *sep;
    char    *start;
    
    head = NULL;
    while (*envp)
    {
        start = *envp;
        sep = ft_strchr(start, '=');
        if (sep)
        {
            *sep = '\0';
            new = create_env(start, sep + 1);
            if (head == NULL)
                head = new;
            else
                env_add_back(&head, create_env(start, sep + 1));
        }
        envp++;
    }
    return (head);
}

void    print_env(t_env *env)
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