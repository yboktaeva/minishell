/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:47:52 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/09 18:13:49 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "../libft/libft.h"
#include <stdlib.h>

static void	init_if_dollar(int *i, int *j, int *double_quote);

void	*expand_word_token(t_env *env, t_token *tokens, t_table *info)
{
	int		i;
	char	*expand_value;

	i = 0;
	while (i < info->n_tokens)
	{
		if (tokens[i].type == WORD && dollar_sign(tokens[i].value) == 1)
		{
			expand_value = if_dollar(env, tokens[i].value);
			if (expand_value == NULL)
				return (NULL);
			if (ft_strcmp(expand_value, tokens[i].value) != 0)
			{
				free(tokens[i].value);
				tokens[i].value = expand_value;
			}
		}
		i++;
	}
	return (SUCCES);
}

char	*if_dollar(t_env *env, char *expand_str)
{
	int	i;
	int	j;
	int	double_quote;

	init_if_dollar(&i, &j, &double_quote);
	while (expand_str[i])
	{
		if (expand_str[i] == '\"')
			double_quote = !double_quote;
		if (expand_str[i] == '\'' && double_quote == 0)
			skip_single_quote(expand_str, &i);
		else if (expand_str[i] == '\\' && expand_str[i + 1] == '$')
		{
			j = i;
			while (expand_str[j])
			{
				expand_str[j] = expand_str[j + 1];
				j++;
			}
		}
		else if (expand_str[i] == '$' && (i == 0 || expand_str[i - 1] != '\\'))
			join_before_and_after(env, &expand_str, &i);
		i++;
	}
	return (expand_str);
}

static void	init_if_dollar(int *i, int *j, int *double_quote)
{
	*i = 0;
	*j = 0;
	*double_quote = 0;
}
