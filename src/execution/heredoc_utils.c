/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:35:48 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/09/23 22:44:30 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <stdlib.h>

static t_here_doc  *new_node(int fd);

int create_tmp_file(t_redir *input)
{
    int fd;
    
    fd = (input->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
        open_error(input->file_name, HEREDOC);
    return (fd);
}

void    add_back_heredoc(t_here_doc *here_doc, int fd)
{
    t_here_doc  *curr;
    
    here_doc = curr;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = new_node(fd);
}

static t_here_doc  *new_node(int fd)
{
    t_here_doc  *new;
    
    new = malloc(sizeof(t_here_doc));
    if (!new)
        return (NULL);
    new->read_fd = fd;
    new->next = NULL;
    return (new); 
}

void    free_n_close_heredoc(t_here_doc *head, int fd)
{
    t_here_doc  *curr;
    t_here_doc  *stock;
    
    if (fd != 0)
        close(fd);
    curr = head;
    while (curr)
    {
        stock = curr->next;
        if (curr->read_fd != 0)
            close(curr->read_fd);
        free(curr);
        curr = stock;
    }
    head = NULL;
}