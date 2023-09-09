/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analyse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:53:00 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/09 21:25:31 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void	delete_quotes(t_token *tokens, int n_tokens);
void	get_rid_quotes(char *value);
void	if_quotes_in_quotes(char *str, char quote_flag, int *i, int *j);
int		if_quotes_closed(char *str);

t_token	*tokenize_input(t_env *env, char *line, t_table *info)
{
	t_token	*tokens;

	info->n_tokens = count_tokens(line);
	if (info->n_tokens < 0)
		return (NULL);
	tokens = malloc(sizeof(struct s_token) * info->n_tokens);
	if (!tokens)
		return (NULL);
	tokens = split_tokens(line, tokens);
	expand_word_token(env, tokens, info);
	delete_quotes(tokens, info->n_tokens);
	return (tokens);
}

void	delete_quotes(t_token *tokens, int n_tokens)
{
	int	i;

	i = 0;
	while (i < n_tokens)
	{
		if (is_word(tokens[i].type))
			get_rid_quotes(tokens[i].value);
		i++;
	}
}

void	get_rid_quotes(char *value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '\'')
			if_quotes_in_quotes(value, '\'', &i, &j);
		else if (value[i] == '\"')
			if_quotes_in_quotes(value, '\"', &i, &j);
		else
		{
			value[j] = value[i];
			j++;
			i++;
		}
	}
	value[j] = '\0';
}

void	if_quotes_in_quotes(char *str, char quote_flag, int *i, int *j)
{
	if (if_quotes_closed(str + *i))
	{
		while (str[*i])
		{
			str[*j] = str[*i];
			(*j)++;
			(*i)++;
		}
	}
	else
	{
		(*i)++;
		while (str[*i] != quote_flag)
		{
			str[*j] = str[*i];
			(*i)++;
			if (str[*i] != '\0')
				(*j)++;
		}
		(*i)++;
	}
}

int	if_quotes_closed(char *str)
{
	int	i;
	int	quote_flag;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote_flag = str[i];
			i++;
			while (str[i] && str[i] != quote_flag)
				i++;
			if (str[i] == '\0')
				return (1);
			i++;
		}
	}
	return (0);
}
