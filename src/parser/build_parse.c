/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:10:29 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/27 15:18:31 by yuboktae         ###   ########.fr       */
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

	is_correct = 0;
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
		syntax_error(tokens[*j].value);
	return (SUCCES);
}
