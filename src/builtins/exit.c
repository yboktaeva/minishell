/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:07:41 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/24 18:30:12 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

extern long long	g_status;

static void	exit_non_numeric_arg(void);
static long long	ft_atoll(const char *str);
static bool	fits_in_longlong(char *str);
static bool	digits_or_signals(char *str);

int	cmd_exit(t_one_cmd *one_cmd)
{
	if (one_cmd != NULL)
	{
		if (num_args(one_cmd) > 2)
		{
			g_status = EXIT_FAILURE;
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		}
		else if (one_cmd->next == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			g_status = EXIT_SUCCESS;
			exit(0);
		}
		else
		{
			if (digits_or_signals(one_cmd->next->str))
			{
				if (!fits_in_longlong(one_cmd->next->str))
					exit_non_numeric_arg();
				else
					g_status = ft_atoll(one_cmd->next->str);
			}
		}
	}
	//if (info)
		//fonction qui nettoie la structure info
	return(g_status);
}

static void	exit_non_numeric_arg(void)
{
	g_status = 2;
	ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
}

static long long	ft_atoll(const char *str)
{
	long long	res;
	int			signal;
	int			i;

	res = 0;
	signal = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i += 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -1;
		i += 1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i += 1;
	}
	return (res * signal);
}

static bool	fits_in_longlong(char *str)
{
	long long	out;
	int			c;

	if (ft_strlen(str) > 20)
		return (false);
	if (ft_strcmp("-9223372036854775808", str) == 0)
		return (true);
	out = 0;
	if (*str == '-' || *str == '+')
		str += 1;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		c = *str - '0';
		if (out > (LLONG_MAX - c) / 10)
			return (false);
		out = out * 10 + c;
		str += 1;
	}
	return (true);
}

static bool	digits_or_signals(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (false);
		i += 1;
	}
	return (true);
}
