/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:23:38 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/10/01 12:59:06 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	free_all(t_table *main, int n_tokens)
{
	if (main->tokens != NULL)
		free_token(main->tokens, n_tokens);
	if (main->parse_list != NULL)
		main->parse_list = free_parse_list(main->parse_list);
}

void	free_token(t_token *tokens, int n_tokens)
{
	int	i;

	i = 0;
	while (i < n_tokens)
	{
		free(tokens[i].value);
		tokens[i].value = NULL;
		i++;
	}
	free(tokens);
	tokens = NULL;
	return ;
}

void	*free_parse_list(t_parse_list *head)
{
	t_parse_list	*tmp;

	if (head == NULL)
		return (NULL);
	tmp = head;
	while (head)
	{
		tmp = head->next;
		if (head->one_cmd)
			head->one_cmd = free_one_cmd_list(head->one_cmd);
		if (head->input)
			head->input = free_redirect_list(head->input);
		if (head->output)
			head->output = free_redirect_list(head->output);
		free(head);
		head = tmp;
	}
	return (NULL);
}

void	*free_one_cmd_list(t_one_cmd *head)
{
	t_one_cmd	*tmp;

	if (head == NULL)
		return (NULL);
	while (head)
	{
		tmp = head->next;
		free(head->str);
		head->str = NULL;
		free(head);
		head = tmp;
	}
	return (NULL);
}

void	*free_redirect_list(t_redir *head)
{
	t_redir	*tmp;

	if (head == NULL)
		return (NULL);
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
		tmp = NULL;
	}
	return (NULL);
}
