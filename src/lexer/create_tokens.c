/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:59:20 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/07 19:00:45 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void	token_quotes(char **start, char **quote_start, t_token *tokens, int *j);
void	token_redirection(char **start, char **end, t_token *tokens, int *j);
void	token_pipe(char **start, t_token *tokens, int *j);
void	token_word(char **start, char **end, t_token *tokens, int *j);

t_token	*split_tokens(char *line, t_token *tokens)
{
	int		j;
	char	*start;
	char	*end;
	char	*quote_start;

	j = 0;
	start = line;
	quote_start = NULL;
	while (*start)
	{
		start = pass_white_space(start);
		if (*start == '\0')
			break ;
		if (*start == '\'' || *start == '\"')
			token_quotes(&start, &quote_start, tokens, &j);
		else if (quote_start == NULL)
		{
			if (*start == '<' || *start == '>')
				token_redirection(&start, &end, tokens, &j);
			else if (*start == '|')
				token_pipe(&start, tokens, &j);
			else
				token_word(&start, &end, tokens, &j);
		}
		start++;
	}
	return (tokens);
}

void	token_quotes(char **start, char **quote_start, t_token *tokens, int *j)
{
	char	quote_type;
	int		len;

	*quote_start = *start;
	quote_type = **start;
	(*start)++;
	while (**start != quote_type && **start != '\0')
		(*start)++;
	len = *start - *quote_start + 1;
	tokens[*j].type = WORD;
	tokens[*j].value = ft_calloc(len + 1, sizeof(char));
	my_strncpy(tokens[*j].value, *quote_start, len);
	(*j)++;
	*quote_start = NULL;
}

void	token_redirection(char **start, char **end, t_token *tokens, int *j)
{
	int	len;
	int	is_less_than;

	len = 1;
	*end = *start;
	if (**end == '<' || **end == '>')
	{
		is_less_than = (**end == '<');
		(*end)++;
		if (**end == **start)
		{
			if (is_less_than)
				tokens[*j].type = HEREDOC;
			else
				tokens[*j].type = APPEND;
			len += 1;
		}
		else
		{
			if (is_less_than)
				tokens[*j].type = REDIR_IN;
			else
				tokens[*j].type = REDIR_OUT;
			(*end)--;
		}
	}
	tokens[*j].value = ft_calloc(len + 1, sizeof(char));
	my_strncpy(tokens[*j].value, *start, len);
	(*j)++;
	*start = *end;
}

void	token_pipe(char **start, t_token *tokens, int *j)
{
	char	*end;
	int		len;

	len = 0;
	end = *start;
	if (*end == '|')
	{
		tokens[*j].type = PIPE;
		len += 1;
		tokens[*j].value = ft_calloc(len + 1, sizeof(char));
		my_strncpy(tokens[*j].value, *start, len);
		(*j)++;
	}
}

void	token_word(char **start, char **end, t_token *tokens, int *j)
{
	*end = *start;
	while (**end && **end != '\'' && **end != '\"'
		&& **end != '<' && **end != '>' && **end != '|' && !ft_isspace(**end))
		(*end)++;
	tokens[*j].type = WORD;
	tokens[*j].value = calloc(*end - *start + 1, sizeof(char));
	my_strncpy(tokens[*j].value, *start, *end - *start);
	(*j)++;
	*start = *end - 1;
}