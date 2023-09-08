/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:09:52 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/08 19:49:35 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "minishell.h"
#include <stddef.h>

static int	count_quotes_token(char **start, char **quote_start);

void	init_var_count_tokens(char *line, int *count, char **start, \
	char **quote_start)
{
	*count = 0;
	*start = line;
	*quote_start = NULL;
}

void	check_and_handle_redir(char **curr, char operator)
{
	if (**curr == operator)
	{
		(*curr)++;
		if (**curr != operator)
			(*curr)--;
	}
}

int	check_and_handle_quotes(char **start, char **quote_start, int *count)
{
	if (count_quotes(*start) != 0)
	{
		quote_error();
		return (-1);
	}
	else
		*count += count_quotes_token(start, quote_start);
	return (0);
}

static int	count_quotes_token(char **start, char **quote_start)
{
	int		count;
	char	quote;

	count = 0;
	*quote_start = *start;
	quote = **start;
	(*start)++;
	while (**start != quote && **start != '\0')
		(*start)++;
	*quote_start = NULL;
	count++;
	return (count);
}