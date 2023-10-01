/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:30:10 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/01 17:22:38 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

static t_here_doc	*run_heredoc(t_redir *input,
						t_here_doc *here_doc, t_cmd_info *cmd_info);
static int			write_heredoc(int *tmp_fd, char *sep);

t_here_doc	*open_heredoc(t_parse_list *parse_list, t_cmd_info *cmd_info)
{
	t_here_doc	*here_doc;
	t_redir		*curr;

	here_doc = malloc(sizeof(t_here_doc));
	if (!here_doc)
	{
		perror("Malloc failure in open heredoc");
		return (NULL);
	}
	here_doc->read_fd = 0;
	here_doc->next = NULL;
	while (parse_list)
	{
		curr = parse_list->input;
		if (curr != NULL)
		{
			if (!run_heredoc(curr, here_doc, cmd_info))
				return (NULL);
		}
		parse_list = parse_list->next;
	}
	return (here_doc);
}

static t_here_doc	*run_heredoc(t_redir *input, t_here_doc *here_doc,
						t_cmd_info *cmd_info)
{
	pid_t	pid;
	int		status;

	while (input != NULL)
	{
		if (input->type == HEREDOC)
		{
			pid = fork();
			if (pid == 0)
			{
				cmd_info->fd[0] = 0;
				cmd_info->fd[1] = 1;
				write_heredoc(cmd_info->fd, input->file_name);
			}
			else
			{
				wait(&status);
				add_back_heredoc(here_doc, cmd_info->in);
			}
		}
		input = input->next;
	}
	return (here_doc);
}

static int	write_heredoc(int *tmp_fd, char *sep)
{
	char	*input;

	handle_sig(SIG_HEREDOC);
	*tmp_fd = open(sep, O_WRONLY | O_CREAT | O_APPEND, 0600);
	while (1)
	{
		input = readline(">");
		if (!input)
			break ;
		else
		{
			if (ft_strncmp(sep, input, ft_strlen(sep)))
			{
				write(tmp_fd[0], input, ft_strlen(input));
				write(tmp_fd[0], "\n", 1);
				free(input);
			}
			else
				break ;
		}
	}
	unlink(sep);
	free(input);
	close(tmp_fd[0]);
	close(tmp_fd[1]);
	exit(0);
}
