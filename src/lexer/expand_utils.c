/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:26:00 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/27 11:04:18 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "../libft/libft.h"
#include <stdlib.h>

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

int	dollar_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?'|| str[i] == '_' || ft_isalpha(str[i]) || ft_isdigit(str[i]))
				return (1);
			else if (str[i] == '\0')
				return (0);
		}
		i++;
	}
	return (0);
}
