/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:50:19 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/22 15:55:52 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void    free_env(t_env **head)
{
    t_env   *tmp;
    t_env   *stock;
    
    if (!(*head))
        return ;
    tmp = *head;
    stock = NULL;
    while (tmp != NULL)
    {
        stock = tmp->next;
        free(tmp);
        tmp = stock;
    }
    *head = NULL;
}