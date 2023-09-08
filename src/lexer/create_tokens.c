/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:59:20 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/08 19:15:20 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include <stddef.h>

static void	init_var_split_tokens(char *line, int *j, char **start, \
		char **quote_start);

t_token	*split_tokens(char *line, t_token *tokens)
{
	int		j;
	char	*start;
	char	*end;
	char	*quote_start;

	init_var_split_tokens(line, &j, &start, &quote_start);
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

static void	init_var_split_tokens(char *line, int *j, char **start, \
		char **quote_start)
{
	*j = 0;
	*start = line;
	*quote_start = NULL;
}
