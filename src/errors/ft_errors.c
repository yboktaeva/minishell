/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 10:44:17 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/15 14:20:56 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    *quote_error(void)
{
    ft_putendl_fd("minishell: quotes are not closed", 2);
    return (NULL);
}

void    *syntax_error(void)
{
    ft_putendl_fd("minishell: syntax error near unexpected token", 2);
    return (NULL);
}
