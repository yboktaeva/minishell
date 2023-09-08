/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:22:12 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/08 19:22:14 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "../libft/libft.h"
#include <stdlib.h>

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

static int	determine_redirection_type(char **end, char **start, \
		int is_less_than, t_token *curr_token)
{
	int	len;

	len = 1;
	if (**end == **start)
	{
		if (is_less_than)
			curr_token->type = HEREDOC;
		else
			curr_token->type = APPEND;
		len += 1;
	}
	else
	{
		if (is_less_than)
			curr_token->type = REDIR_IN;
		else
			curr_token->type = REDIR_OUT;
		(*end)--;
	}
	return (len);
}

void	token_redirection(char **start, char **end, t_token *tokens, int *j)
{
	int	len;
	int	is_less_than;

	len = 0;
	*end = *start;
	if (**end == '<' || **end == '>')
	{
		is_less_than = (**end == '<');
		(*end)++;
		len += determine_redirection_type(end, start, \
		is_less_than, &tokens[*j]);
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
	tokens[*j].value = ft_calloc(*end - *start + 1, sizeof(char));
	my_strncpy(tokens[*j].value, *start, *end - *start);
	(*j)++;
	*start = *end - 1;
}
