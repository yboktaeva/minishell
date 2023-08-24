/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 10:44:17 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/24 10:59:49 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void    *quote_error(void)
{
    ft_putendl_fd("minishell: missing closing quote", 2);
    return (NULL);
}

void    *syntax_error(char *str)
{
    printf("minishell: syntax error near unexpected token `%s'\n", str);
    return (NULL);
}
