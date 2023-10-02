/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:30:10 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/02 17:38:28 by yuboktae         ###   ########.fr       */
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

static t_here_doc	*run_heredoc(t_table *main, t_redir *input,
						t_here_doc *here_doc, t_cmd_info *cmd_info);
static int			write_heredoc(t_table *main, int *tmp_fd, char *sep);

void open_heredoc(t_table *main, t_parse_list *parse_list, t_cmd_info *cmd_info)
{
	t_redir		*curr;

	main->here_doc = malloc(sizeof(t_here_doc));
	if (!main->here_doc)
	{
		perror("Malloc failure in open heredoc");
		return ;
	}
	main->here_doc->read_fd = 0;
	main->here_doc->next = NULL;
	while (parse_list)
	{
		curr = parse_list->input;
		if (curr != NULL)
		{
			if (!run_heredoc(main, curr, main->here_doc, cmd_info))
			{
				free_n_close_heredoc(&main->here_doc, 0);
				return (free(main->here_doc));
			}
		}
		parse_list = parse_list->next;
	}
}

static t_here_doc	*run_heredoc(t_table *main, t_redir *input, t_here_doc *here_doc,
						t_cmd_info *cmd_info)
{
	pid_t	pid;
	int		status;
(void)here_doc;
	while (input != NULL)
	{
		if (input->type == HEREDOC)
		{
			pid = fork();
			if (pid == 0)
			{
				cmd_info->fd[0] = 0;
				cmd_info->fd[1] = 1;
				write_heredoc(main, cmd_info->fd, input->file_name);
			}
			else
			{
				waitpid(pid, &status, 0);
				add_back_heredoc(main->here_doc, cmd_info->in);
			}
		}
		input = input->next;
	}
	return (main->here_doc);
}

static int	write_heredoc(t_table *main, int *tmp_fd, char *sep)
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
			}
			else
			{
				free(input);
				break ;
			}
		}
	}
	unlink(sep);
	close(tmp_fd[0]);
	close(tmp_fd[1]);
	free_env(&main->env);
	free_execution(main);
	free_n_close_heredoc(&main->here_doc, 0);
	exit(0);
}
