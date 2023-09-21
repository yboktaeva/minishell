/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:35:34 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/21 17:19:58 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

static int	check_n_option(char *str, char c);
static int	if_n_option(t_one_cmd *one_cmd);
static void	print_echo(t_one_cmd *one_cmd);

int	cmd_echo(t_one_cmd *one_cmd)
{
	int	n_flag;

	n_flag = 0;
	if (one_cmd->next == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	one_cmd = one_cmd->next;
	while (one_cmd)
	{
		if (if_n_option(one_cmd))
		{
			n_flag = 1;
			one_cmd = one_cmd->next;
		}
		else
			break ;
	}
	print_echo(one_cmd);
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}

static void	print_echo(t_one_cmd *one_cmd)
{
	while (one_cmd)
	{
		ft_putstr_fd(one_cmd->str, 1);
		if (one_cmd->next != NULL)
			ft_putchar_fd(' ', 1);
		one_cmd = one_cmd->next;
	}
}

static int	if_n_option(t_one_cmd *one_cmd)
{
	if (one_cmd->str[0] != '-')
		return (0);
	if (check_n_option(&one_cmd->str[1], 'n'))
		return (1);
	return (0);
}

static int	check_n_option(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}
