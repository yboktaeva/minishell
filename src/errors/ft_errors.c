/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 10:44:17 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/23 17:57:44 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stddef.h>

void	quote_error(void)
{
	ft_putendl_fd("minishell: missing closing quote", 2);
	g_status = 1;
	exit(1);
}

void	syntax_error(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	g_status = 2;
	exit(2);
}

void	open_error(char *str, t_type type)
{
	if (type == REDIR_IN)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else if (type == REDIR_OUT || type == APPEND)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": cannot open output file", 2);
	}
	g_status = 2;
	exit(2);
}

void	chdir_error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": No such file or directory", 2);
	g_status = 2;
	exit(2);
}

void	command_not_found(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
	g_status = 127;
	exit(127);
}

void	exec_fail(void)
{
	perror("execve");
	g_status = 2;
	exit(2);
}