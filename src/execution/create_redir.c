/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:10:56 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/09/12 20:27:25 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <unistd.h>
#include <stdio.h>

static void open_input(t_redir *input, int *fd_in, t_here_doc *here_doc);
static void open_output(t_redir *output, int *fd_out);

void    handle_redirections(t_parse_list *parse_list, int *fd_in, int *fd_out, t_here_doc *here_doc)
{
    if (parse_list->input)
        open_input(parse_list->input, fd_in, here_doc);
    if (parse_list->output)
        open_output(parse_list->output, fd_out);
}

static void open_input(t_redir *input, int *fd_in, t_here_doc *here_doc)
{
    while (input)
    {
        if (input->type == REDIR_IN)
        {
            *fd_in = open(input->file_name, O_RDONLY);
            if (*fd_in == -1) 
            {
                perror("Erreur lors de l'ouverture du fichier d'entrée");
                exit(1);
            }   
        }
        else
        {
            *fd_in = here_doc->read;
            here_doc = here_doc->next;
        }
        input = input->next;
    }
}

static void open_output(t_redir *output, int *fd_out)
{
    while (output)
    {
        if (output->type == REDIR_OUT)
        {
            *fd_out = open(output->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (*fd_out == -1) 
            {
                perror("Erreur lors de l'ouverture du fichier de sortie");
                exit(1);
            }
        }
        else
        {
            *fd_out = open(output->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (*fd_out == -1) 
            {
                perror("Erreur lors de l'ouverture du fichier de sortie");
                exit(1);
            }
        }
        output = output->next;
    }
}

t_here_doc    *open_heredoc(t_parse_list *parsing_list)
{
    t_here_doc *here_doc;

    here_doc = malloc(sizeof(t_here_doc));
    if (!here_doc)
    {
		perror("Malloc failure in duplicate envp");
		return (NULL);
	}
    here_doc->read = 0;
    here_doc->next = NULL;
    while (parsing_list)
    {
        if (parsing_list->input->type == HEREDOC)
    }
    return (here_doc);
}