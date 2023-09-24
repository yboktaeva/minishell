/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:30:10 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/24 02:00:31 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static t_here_doc  *run_heredoc(t_redir *input, t_here_doc *here_doc);
static int write_heredoc(int tmp_fd, char *sep);

t_here_doc    *open_heredoc(t_parse_list *parse_list)
{
    t_here_doc *here_doc;
    t_redir *curr;
    
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
            if (!run_heredoc(curr, here_doc))
                return (NULL);
        }
        parse_list = parse_list->next;
    }
    return (here_doc);
}

static t_here_doc  *run_heredoc(t_redir *input, t_here_doc *here_doc)
{
	pid_t	pid;
    int status;
    int fd[2];
    
    while (input)
    {
        if (input->type == HEREDOC)
        {
            pid = fork;
            if (pid == 0)
                write_heredoc(fd, input->file_name);
            else
            {
                close(fd[1]);
                wait(&status);
                add_back_heredoc(here_doc, fd);
            }
        }
        input = input->next;
    }
    return (here_doc);
}

static int write_heredoc(int tmp_fd, char *sep)
{
    char    *input;
    
    handle_sig(SIG_HEREDOC);
    while (1)
    {
        input = readline(">");
        if (!input)
        {
            close(tmp_fd);
            exit(0);
        }
        if (ft_strncmp(sep, input, ft_strlen(sep + 1)))
            ft_putendl_fd(input, tmp_fd);
        else
        {
            close(tmp_fd);
            free(input);
            break ;
        }
    }
    free(input);
    close(tmp_fd);
    exit(0);
}