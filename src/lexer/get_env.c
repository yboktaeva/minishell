/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:08:15 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/29 19:08:48 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void    set_env_list(t_env **head, char **envp);
void	get_env(t_env *head, char *str);
t_env   *add_env_node(char *str);
t_env   *copy_env(t_env *env, char *str);

t_env   *init_env_list(char **envp)
{
    t_env  *head;

    head = malloc(sizeof(t_env));
    if (!head)
        return (NULL);
    head->key = NULL;
    head->value = NULL;
    head->str = NULL;
    head->next = NULL;
    set_env(head, envp);
    return (head);
}

void    set_env_list(t_env **head, char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        get_env(head, envp[i]);
        i++;
    }
}

void	get_env(t_env *head, char *str)
{
    t_env   *start;
    t_env   *copy;
    int     index;
    
    copy = copy_env(head, str);
    index = ft_strchr(str, '=') - str + 1;
    if (copy)
    {
        if (env_key_len(str) == ft_strlen(str))
            return ;
        free(copy->str);
        if (copy->value != NULL)
            free(copy->value);
        copy->str = ft_strdup(str);
        copy->value = ft_substr(str, index, ft_strlen(str));
        return ;
    }
    start = head;
    while(start->next != NULL)
        start = start->next;
    start->next = add_env_node(str);
}

t_env   *add_env_node(char *str)
{
    t_env *new;
    int     index;

    index = ft_strchr(str, '=') - str;
    new = malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->str = ft_strdup(str);
    new->key = ft_substr(str, 0, env_key_len(str));
    if (!index)
        new->value = NULL;
    else
        new->value = ft_substr(str, index + 1, ft_strlen(str));
    new->next = NULL;
    return (new);
}

t_env   *copy_env(t_env *env, char *str)
{
    t_env   *start;
    char    *key;
    int     key_len;
    
    key = env_key(str);
    key_len = ft_strlen(key);
    start = env;
    while (start)
    {
        if (ft_strncmp(start->key, key, key_len + 1) == 0)
        {
            free(key);
            return (start);
        }
        start = start->next;
    }
    free(key);
    return (NULL);
}