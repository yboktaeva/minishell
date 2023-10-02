/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:35:48 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/10/02 17:25:22 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static t_here_doc	*new_node(int fd);

void	add_back_heredoc(t_here_doc *here_doc, int fd)
{
	t_here_doc	*curr;

	curr = here_doc;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node(fd);
}

static t_here_doc	*new_node(int fd)
{
	t_here_doc	*new;

	new = malloc(sizeof(t_here_doc));
	if (!new)
		return (NULL);
	new->read_fd = fd;
	new->next = NULL;
	return (new);
}

void	free_n_close_heredoc(t_here_doc **head, int fd)
{
	t_here_doc	*curr;
	t_here_doc	*stock;

	ft_close(fd);
	curr = *head;
	stock = NULL;
	while (curr)
	{
		stock = curr->next;
		ft_close(curr->read_fd);
		free(curr);
		curr = stock;
	}
	*head = NULL;
}
