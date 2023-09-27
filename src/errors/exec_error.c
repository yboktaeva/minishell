/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:59:21 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/27 19:07:41 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

void	*exec_fail(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
    ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	g_status = 127;
	return (NULL);
}