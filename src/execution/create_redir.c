/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:10:56 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/09/17 22:46:00 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
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
                open_error(input->file_name, REDIR_IN);
                return (-1);
            }   
        }
        // else if (input->type == HEREDOC)
        // {
        //     *fd_in = here_doc->read;
        //     here_doc = here_doc->next;
        //     if (*fd_in == -1) 
        //     {
        //         open_error(input->file_name);
        //         return (-1);
        //     }   
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
                open_error(output->file_name, REDIR_OUT);
                return (-1);
            }
        }
        else if (output->type == APPEND)
        {
            *fd_out = open(output->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (*fd_out == -1) 
            {
                open_error(output->file_name, APPEND);
                return (-1);
            }
        }
        output = output->next;
    }
    return (0);
}