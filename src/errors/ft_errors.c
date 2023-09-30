/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 10:44:17 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/29 12:05:22 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	*quote_error(void)
{
	ft_putendl_fd("minishell: missing closing quote", STDERR_FILENO);
	g_status = 1;
	return (NULL);
}

void	*syntax_error(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	g_status = 2;
	return (NULL);
}

void	*open_error(char *str, t_type type)
{
	if (type == REDIR_IN)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	else if (type == REDIR_OUT || type == APPEND)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": cannot open output file", STDERR_FILENO);
	}
	g_status = 2;
	return (NULL);
}

void	*chdir_error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	g_status = 2;
	return (NULL);
}
