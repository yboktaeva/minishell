/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fd_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:34:17 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/22 11:31:34 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int open_input(t_redir *input, int *fd_in);
int open_output(t_redir *output, int *fd_out);

int   handle_redirections(t_parse_list *parse_list, int *fd_in, int *fd_out)
{
    
    if (parse_list->input != NULL)
        open_input(parse_list->input, fd_in);
    if (parse_list->output != NULL)
        open_output(parse_list->output, fd_out);
    return (1);
}

int open_input(t_redir *input, int *fd_in)
{
    if (!input || !fd_in)
        return (0);
    if (*fd_in != 0)
        close(*fd_in);
    while (input)
    {
        if (input->type == REDIR_IN)
        {
            *fd_in = open(input->file_name, O_RDONLY);
            if (*fd_in == -1) 
            {
                open_error(input->file_name, REDIR_IN);
                exit (1);
            }   
        }
        // else if (input->type == HEREDOC)
        // {
        //     *fd_in = here_doc->read;
        //     here_doc = here_doc->next;
        //     if (*fd_in == -1) 
        //     {
        //         open_error(input->file_name);
        //         exit (1);
        //     }   
        // }
        if (input->next)
            close(*fd_in);
        input = input->next;
    }
    return (1);
}

int open_output(t_redir *output, int *fd_out)
{
    if (!output || !fd_out)
        return (0);
    if (*fd_out != 1)
        close(*fd_out);
    while (output)
    {
        if (output->type == REDIR_OUT)
        {
            *fd_out = open(output->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (*fd_out == -1) 
            {
                open_error(output->file_name, REDIR_OUT);
                exit (1);
            }
        }
        else if (output->type == APPEND)
        {
            *fd_out = open(output->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (*fd_out == -1) 
            {
                open_error(output->file_name, APPEND);
                exit (1);
            }
        }
        if (output->next)
            close(*fd_out);
        output = output->next;
    }
    return (1);
}