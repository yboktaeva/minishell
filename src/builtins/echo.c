/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:35:34 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/06 18:23:30 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	is_n_option(t_one_cmd *one_cmd);

// static void	print(int i, char **str, int out)
// {
// 	while (str[i])
// 	{
// 		ft_putstr_fd(str[i++], out);
// 		if (str[i])
// 			ft_putchar_fd(' ', out);
// 	}
// }

// int	cmd_echo(t_table *info, char **argv)
// {
// 	int		i;
// 	int		j;
// 	int     n;
//     (void) info;

// 	i = 1;
// 	n = 0;
// 	while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
// 	{
// 		j = 1;
// 		while (argv[i][j] == 'n')
// 			j++;
// 		if (argv[i][j] == '\0')
// 			n = 1;
// 		else
// 			break ;
// 		i++;
// 	}
// 	print(i, argv, STDOUT_FILENO);
// 	if (n == 0)
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 	return (EXIT_SUCCESS);
// }

int     cmd_echo(t_one_cmd *one_cmd)
{
	int	echo_status;
	int	n_flag;

	echo_status = 0;
	n_flag = 1;
	if (one_cmd->next == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (echo_status);
	}
	one_cmd = one_cmd->next;
	if (is_n_option(one_cmd))
	{
		echo_status = 0;
		one_cmd = one_cmd->next;
	}
	while (one_cmd)
	{
		ft_putstr_fd(one_cmd->str, 1);
		if (one_cmd->next != NULL)
			ft_putchar_fd(' ', 1);
		one_cmd = one_cmd->next;
	}
	if (n_flag)
		ft_putstr_fd("\n", 1);
	return (echo_status = 0);
}

int	is_n_option(t_one_cmd *one_cmd)
{
	if (one_cmd->str[0] != '-')
		return (0);
	if (ft_strcmp(&one_cmd->str[1], "n") == 0)
		return (1);
	return (0);
}