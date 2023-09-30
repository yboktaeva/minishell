/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fd_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:34:17 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/30 12:01:34 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int	open_input(t_redir *input, t_here_doc *here_doc, int *fd_in);
static int	open_output(t_redir *out, int *fd_out);

int	handle_redirections(t_parse_list *parse_list, t_here_doc *here_doc,
				int *fd_in, int *fd_out)
{
	int	status;

	status = 1;
	if (parse_list->input != NULL)
		status = open_input(parse_list->input, here_doc, fd_in);
	if (parse_list->output != NULL)
		status = open_output(parse_list->output, fd_out);
	return (status);
}

static int	open_input(t_redir *input, t_here_doc *here_doc, int *fd_in)
{
	check_fd_in(input, fd_in);
	while (input)
	{
		if (input->type == REDIR_IN)
		{
			*fd_in = open(input->file_name, O_RDONLY);
			if (*fd_in == -1)
			{
				open_error(input->file_name, REDIR_IN);
				return (0);
			}
		}
		else if (input->type == HEREDOC)
		{
			*fd_in = here_doc->read_fd;
			here_doc = here_doc->next;
			if (*fd_in == -1)
			{
				open_error(input->file_name, HEREDOC);
				return (0);
			}
		}
		file_next(&input, fd_in);
	}
	return (1);
}

static int	open_output(t_redir *out, int *fd_out)
{
	check_fd_out(out, fd_out);
	while (out)
	{
		if (out->type == REDIR_OUT)
		{
			*fd_out = open(out->file_name,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*fd_out == -1)
			{
				open_error(out->file_name, REDIR_OUT);
				return (0);
			}
		}
		else if (out->type == APPEND)
		{
			*fd_out = open(out->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (*fd_out == -1)
			{
				open_error(out->file_name, APPEND);
				return (0);
			}
		}
		file_next(&out, fd_out);
	}
	return (1);
}
