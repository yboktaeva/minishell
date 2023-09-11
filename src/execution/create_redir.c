/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:10:56 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/09/12 00:35:13 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <unistd.h>
#include <stdio.h>

static void   open_input(t_redir *input, int *fd_in);
static void    open_output(t_redir *output, int *fd_out);

void    handle_redirections(t_parse_list *parse_list, int *fd)
{
    if (parse_list->input)
        open_input(parse_list->input, fd);
    if (parse_list->output)
        open_output(parse_list->output, fd);
}

void   open_input(t_redir *input, int *fd_in)
{
    while (input)
    {
        if (input->type == REDIR_IN)
        {
            *fd_in = open(tmp->input->file_name, O_RDONLY);
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

void    open_output(t_redir *output, int *fd_out)
{
    while (output)
    {
        if (output->type == REDIR_OUT)
        {
            *fd_out = open(tmp->output->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (*fd_out == -1) 
            {
                perror("Erreur lors de l'ouverture du fichier de sortie");
                exit(1);
            }
        }
        else
        {
            *fd_out = open(tmp->output->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (*fd_out == -1) 
            {
                perror("Erreur lors de l'ouverture du fichier de sortie");
                exit(1);
            }
        }
        output = output->next;
    }
}