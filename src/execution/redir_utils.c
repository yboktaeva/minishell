/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:48:16 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/30 16:40:42 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	check_fd_in(t_redir *file, int *fd_in)
{
	if (!file || !fd_in)
		return ;
	if (*fd_in != 0)
		ft_close(*fd_in);
}

void	check_fd_out(t_redir *file, int *fd_out)
{
	if (!file || !fd_out)
		return ;
	if (*fd_out != 1)
		ft_close (*fd_out);
}

void	file_next(t_redir **file, int *fd)
{
	if ((*file)->next)
		ft_close(*fd);
	*file = (*file)->next;
}

int	handle_io_redir(t_parse_list *s, t_table *main, t_cmd_info *cmd_info)
{
	int	flag_redir;

	flag_redir = 0;
	if (s->input || s->output)
	{
		flag_redir = handle_redirections(s, main->here_doc,
				&cmd_info->in, &cmd_info->out);
		if (flag_redir)
		{
			if (cmd_info->in != STDIN_FILENO)
			{
				dup2(cmd_info->in, STDIN_FILENO);
				ft_close(cmd_info->in);
			}
			if (cmd_info->out != STDOUT_FILENO)
			{
				dup2(cmd_info->out, STDOUT_FILENO);
				ft_close(cmd_info->out);
			}
		}
	}
	return (flag_redir);
}
