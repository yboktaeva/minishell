/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:59:20 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/02 11:19:17 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_token *create_token(t_type type, char *value)
{
    t_token *tok;

    tok = malloc(sizeof(t_token));
    tok->type = type;
    tok->value = ft_strdup(value);
    return (tok);
}

void    free_token(t_token *tok)
{
    free(tok->value);
    free(tok);
}

