/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:10:56 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/09/13 17:20:49 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int open_input(t_redir *input, int *fd_in);
int open_output(t_redir *output, int *fd_out);

void    handle_redirections(t_parse_list *parse_list, int *fd_in, int *fd_out)
{
    if (parse_list->input != NULL)
        open_input(parse_list->input, fd_in);
    if (parse_list->output != NULL)
        open_output(parse_list->output, fd_out);
}

int open_input(t_redir *input, int *fd_in)
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
        // else
        // {
        //     *fd_in = here_doc->read;
        //     here_doc = here_doc->next;
        // }
        input = input->next;
    }
    return (0);
}

int open_output(t_redir *output, int *fd_out)
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
    return (0);
}