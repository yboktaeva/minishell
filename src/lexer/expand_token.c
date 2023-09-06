/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:47:52 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/06 19:19:17 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

char		*find_var_value(t_env *env, char *str, int *i);
void		join_before_and_after(t_env *env, char **str, int *i);
char		*if_dollar(t_env *env, char *expand_str);
static int	dollar_sign(char *str);

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

	i = 0;
	j = 0;
	double_quote = 0;
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

void	join_before_and_after(t_env *env, char **str, int *i)
{
	char	*before_dollar;
	char	*after_dollar;

	before_dollar = ft_substr(*str, 0, *i);
	if ((*str + *i + 1)[0] == '=')
	{
		before_dollar = ft_strjoin(before_dollar, "$=");
		after_dollar = find_var_value(env, *str + *i + 3, i);
		*i += 2;
	}
	else
		after_dollar = find_var_value(env, *str + *i + 1, i);
	*str = ft_strjoin(before_dollar, after_dollar);
	free(before_dollar);
	free(after_dollar);
}

char	*find_var_value(t_env *env, char *str, int *i)
{
	int		var_name_len;
	char	*var_name;
	char	*var_value;
	char	*expand_str;
	char	*after_str;

	var_name_len = env_var_name_len(str);
	var_name = ft_substr(str, 0, var_name_len);
	var_value = env_var_value(env, var_name);
	after_str = ft_substr(str, var_name_len, ft_strlen(str));
	*i = *i + ft_strlen(var_value) - 1;
	expand_str = ft_strjoin(var_value, after_str);
	free(var_value);
	free(var_name);
	free(after_str);
	return (expand_str);
}

static int	dollar_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '_' || ft_isalpha(str[i]) || ft_isdigit(str[i]))
				return (1);
			else if (str[i] == '\0')
				return (0);
		}
		i++;
	}
	return (0);
}
