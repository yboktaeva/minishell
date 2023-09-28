/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:59:21 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/28 22:13:14 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	exec_fail(char *str)
{
	//(void)str;
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	g_status = 127;
	return (g_status);
}