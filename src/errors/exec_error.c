/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:59:21 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/30 18:28:22 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "exec.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	exec_fail(t_table *main, char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	g_status = 127;
	safe_exit(main);
	free_all(main, main->n_tokens);
	free(main->cmd_info->executable_path);
	free_n_close_heredoc(main->here_doc, main->cmd_info->fd[0]);
	free_cmd_args(main->arg->argv);
	check_free(main->cmd_info->fd);
	exit(g_status);
}

void	*path_null(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	g_status = 127;
	return (NULL);
}
