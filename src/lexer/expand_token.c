/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:47:52 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/30 16:50:01 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char    *expand_dollar_sign(t_env *env, char *input)
{
    int var_name_len;
    char *var_name;
    char *var_value;
    char *expand_input;
    char *after_input;

    var_name_len = env_var_name_len(input);
    var_name = ft_substr(input, 0, var_name_len);
    var_value = env_var_value(env, var_name);
    after_input = ft_substr(input, var_name_len, ft_strlen(input));
    expand_input = ft_strjoin(var_value, after_input);
    free(var_value);
    free(var_name);
    free(after_input);
    return (expand_input);
}

