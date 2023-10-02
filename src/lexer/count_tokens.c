/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:32:08 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/02 18:08:29 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stddef.h>

static int	count_redirection(char **start);
static int	count_pipe(char **start);
static int	count_word(char **start);
static void	count_part(char **start, char **quote_start, int *count);

int	count_tokens(char *line)
{
	int		count;
	char	*start;
	char	*quote_start;

	init_var_count_tokens(line, &count, &start, &quote_start);
	while (*start)
	{
		start = pass_white_space(start);
		if (*start == '\0')
			break ;
		if (*start == '\'' || *start == '\"')
		{
			// if (check_and_handle_quotes(&start, &quote_start, &count) == -1)
			// 	return (-1);
			check_and_handle_quotes(&start, &quote_start, &count);
			
		}
		else if (quote_start == NULL)
		{
			count_part(&start, &quote_start, &count);
		}
		start++;
	}
	return (count);
}

static void	count_part(char **start, char **quote_start, int *count)
{
	if (*quote_start == NULL)
	{
		if (**start == '<' || **start == '>')
			*count += count_redirection(start);
		else if (**start == '|')
			*count += count_pipe(start);
		else
			*count += count_word(start);
	}
}

static int	count_pipe(char **start)
{
	int		count;
	char	*current;

	count = 0;
	current = *start;
	if (*current && *current == '|')
		count++;
	*start = current;
	return (count);
}

static int	count_redirection(char **start)
{
	int		count;
	char	*curr;

	count = 0;
	curr = *start;
	{
		if (*curr == '<' || *curr == '>')
		{
			check_and_handle_redir(&curr, '<');
			check_and_handle_redir(&curr, '>');
			count++;
		}
	}
	*start = curr;
	return (count);
}

static int	count_word(char **start)
{
	int		count;
	char	*current;

	count = 0;
	current = *start;
	while (*current && *current != '\'' && *current != '\"'
		&& *current != '<' && *current != '>'
		&& *current != '|' && !ft_isspace(*current))
		current++;
	count++;
	*start = current - 1;
	return (count);
}
