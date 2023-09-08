/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:10:29 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/08 19:51:40 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

static void	*invalid_operator(t_token *tokens, int *j);
static int	fill_parse_list(t_parse_list *parse_list, \
	t_token *tokens, int n_tokens);

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

static int	fill_parse_list(t_parse_list *parse_list, \
	t_token *tokens, int n_tokens)
{
	int	i;

	i = 0;
	while (i < n_tokens)
	{
		if (!invalid_operator(tokens, &i))
			return (-1);
		if (is_word(tokens[i].type))
			if_word_token(tokens, parse_list, &i);
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

static void	*invalid_operator(t_token *tokens, int *j)
{
	if (ft_strcmp(tokens[*j].value, "&") == 0
		|| ft_strcmp(tokens[*j].value, "&&") == 0
		|| ft_strcmp(tokens[*j].value, ";") == 0)
		return (syntax_error(tokens[*j].value));
	return (SUCCES);
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

void	print_parse_list(t_parse_list *parse_list)
{
	t_one_cmd	*cur_cmd;
	t_redir		*cur_redir;

	while (parse_list != NULL)
	{
		cur_cmd = parse_list->one_cmd;
		while (cur_cmd != NULL)
		{
			printf("%s\n", cur_cmd->str);
			cur_cmd = cur_cmd->next;
		}
		cur_redir = parse_list->input;
		while (cur_redir != NULL)
		{
			printf("T: %d, F: %s\n", cur_redir->type, cur_redir->file_name);
			cur_redir = cur_redir->next;
		}
		cur_redir = parse_list->output;
		while (cur_redir != NULL)
		{
			printf("T: %d, F: %s\n", cur_redir->type, cur_redir->file_name);
			cur_redir = cur_redir->next;
		}
		parse_list = parse_list->next;
	}
}
