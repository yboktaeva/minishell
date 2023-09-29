/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:07:41 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/29 10:50:25 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "utils.h"
#include "minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	single_exit(t_table *main);
static int	is_all_digit(char *str);

int	cmd_exit(t_one_cmd *one_cmd, t_table *main)
{
	if (one_cmd->next == NULL)
		single_exit(main);
	else if (one_cmd->next->next != NULL)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (g_status = 1);
	}
	else
	{
		if (is_all_digit(one_cmd->next->str))
		{
			ft_putendl_fd("exit", 1);
			exit(ft_atoi(one_cmd->next->str));
		}
		else
		{
			ft_putendl_fd("minishell: exit: numeric argument required",
				STDERR_FILENO);
			exit(255);
		}
	}
	g_status = 0;
	return (g_status);
}

static void	single_exit(t_table *main)
{
	ft_putendl_fd("exit", 1);
	safe_exit(main);
	exit(g_status);
}

static int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}
