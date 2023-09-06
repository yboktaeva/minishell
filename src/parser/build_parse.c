/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:10:29 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/06 19:33:05 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

t_parse_list	*parsing_tokens(t_token *tokens, int n_tokens)
{
	int				is_correct;
	t_parse_list	*parse_list;

	parse_list = NULL;
	if (!tokens)
		return (NULL);
	parse_list = init_parse_list();
	is_correct = fill_parse_list(parse_list, tokens, n_tokens);
	{
		if (is_correct == -1)
		{
			free_parse_list(parse_list);
			return (NULL);
		}
	}
	return (parse_list);
}

int	fill_parse_list(t_parse_list *parse_list, t_token *tokens, int n_tokens)
{
	int	i;

	i = 0;
	while (i < n_tokens)
	{
		if (is_word(tokens[i].type))
		{
			if (!invalid_operator(tokens, &i))
				return (-1);
			else
				if_word_token(tokens, parse_list, &i);
		}
		else if (is_redir(tokens[i].type))
		{
			if (if_redir_token(tokens, parse_list, &i, n_tokens) == NULL)
				return (-1);
			if (is_word(tokens[i + 1].type))
				i++;
		}
		else
		{
			if (if_pipe_token(tokens, parse_list, &i, n_tokens) == NULL)
				return (-1);
			parse_list = parse_list->next;
		}
		i++;
	}
	return (1);
}

void	*invalid_operator(t_token *tokens, int *j)
{
	if (ft_strcmp(tokens[*j].value, "&") == 0 || ft_strcmp(tokens[*j].value, "&&") == 0
		|| ft_strcmp(tokens[*j].value, ";") == 0)
		return (syntax_error(tokens[*j].value));
	return (SUCCES);
}

void	print_parse_list(t_parse_list *parse_list)
{
	t_one_cmd	*current_cmd;
	t_redir		*current_redir;

	while (parse_list != NULL)
	{
		printf("Commands:\n");
		current_cmd = parse_list->one_cmd;
		while (current_cmd != NULL)
		{
			printf("%s\n", current_cmd->str);
			current_cmd = current_cmd->next;
		}
		printf("Input redirections:\n");
		current_redir = parse_list->input;
		while (current_redir != NULL)
		{
			printf("Type: %d, File: %s\n", current_redir->type, current_redir->file_name);
			current_redir = current_redir->next;
		}
		printf("Output redirections:\n");
		current_redir = parse_list->output;
		while (current_redir != NULL)
		{
			printf("Type: %d, File: %s\n", current_redir->type, current_redir->file_name);
			current_redir = current_redir->next;
		}
		parse_list = parse_list->next;
	}
}

void	print_tokens(t_token *tokens, int n_tokens)
{
	int	i;

	i = 0;
	while (i < n_tokens)
	{
		printf("Tok %d: T = %d, V = %s\n", i, tokens[i].type, tokens[i].value);
		i++;
	}
}
