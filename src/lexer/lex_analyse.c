/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analyse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:53:00 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/02 19:48:50 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "../libft/libft.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void	delete_quotes(t_token *tokens, int n_tokens);
void	get_rid_quotes(char *value);
void	if_quotes_in_quotes(char *str, char quote_flag, int *i, int *j);
int		if_quotes_closed(char *str);
void	remove_empty_tokens(t_token **tokens, int *n_tokens);

t_token	*tokenize_input(t_env *env, char *line, t_table *main)
{
	t_token	*tokens;

	main->n_tokens = count_tokens(line);
	if (main->n_tokens < 0)
		return (NULL);
	tokens = malloc(sizeof(struct s_token) * main->n_tokens);
	if (!tokens)
		return (NULL);
	tokens = split_tokens(line, tokens);
	if (!tokens)
		free_token(tokens, main->n_tokens);
	else
	{
		expand_word_token(env, tokens, main);
		delete_quotes(tokens, main->n_tokens);
	}
	remove_empty_tokens(&tokens, &main->n_tokens);
	return (tokens);
}

void remove_empty_tokens(t_token **tokens, int *n_tokens)
{
    int i;
	int	j;
	
	i = 0;
	j = 0;
    t_token *new_tokens;
	
	new_tokens = malloc(sizeof(t_token) * (*n_tokens));
    if (!new_tokens)
        return ;
    while (i < *n_tokens)
    {
        if (ft_strlen((*tokens)[i].value) > 0)
        {
            new_tokens[j] = (*tokens)[i];
            j++;
        }
        else
            free((*tokens)[i].value);
        i++;
    }
    free(*tokens);
    *tokens = new_tokens;
    *n_tokens = j;
}

static void	remove_extra_spaces(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!(str[i] == ' ' && str[i + 1] == ' '))
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

void	delete_quotes(t_token *tokens, int n_tokens)
{
	int	i;

	i = 0;
	while (i < n_tokens)
	{
		if (is_word(tokens[i].type))
		{
			get_rid_quotes(tokens[i].value);
		}
		i++;
	}
	i = 0;
	while (i < n_tokens)
	{
		if (is_word(tokens[i].type))
		{
			remove_extra_spaces(tokens[i].value);
		}
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


// void	get_rid_quotes(char *value)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (value[i])
// 	{
// 		if (value[i] == '\'')
// 			if_quotes_in_quotes(value, '\'', &i, &j);
// 		else if (value[i] == '\"')
// 			if_quotes_in_quotes(value, '\"', &i, &j);
// 		else
// 		{
// 			value[j] = value[i];
// 			j++;
// 			i++;
// 		}
// 	}
// 	value[j] = '\0';
// }

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
			(*j)++;
			(*i)++;
		}
		(*j)--;
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
