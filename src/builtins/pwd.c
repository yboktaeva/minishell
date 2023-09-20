/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:00:22 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/20 18:26:33 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	cmd_pwd(t_one_cmd *one_cmd)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (one_cmd->str == NULL)
		return (1);
	if (cwd == NULL)
	{
		perror("minishell:");
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
}