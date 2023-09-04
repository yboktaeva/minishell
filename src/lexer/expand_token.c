/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:47:52 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/04 19:52:30 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

char    *expand_dollar_sign(t_env *env, char *str, int *i)
{
    int var_name_len;
    char *var_name;
    char *var_value;
    char *expand_str;
    char *after_str;

    var_name_len = env_var_name_len(str);
    var_name = ft_substr(str, 0, var_name_len);
    var_value = env_var_value(env, var_name);
    after_str = ft_substr(str, var_name_len, ft_strlen(str));
    *i = *i = ft_strlen(var_value) - 1;
    expand_str = ft_strjoin(var_value, after_str);
    free(var_value);
    free(var_name);
    free(after_str);
    return (expand_str);
}

void    expand_and_join(t_env *env, char **str, int *i)
{
    char    *tmp_str;
    char    *before_str;
    char    *after_str;
    
    tmp_str = str;
    before_str = ft_substr(*str, 0, *i);
    after_str = expand_dollar_sign(env, *str + *i + 1, i);
    *str = ft_strjoin(before_str, after_str);
    free(tmp_str);
    free(before_str);
    free(after_str);
}

char    *expand_word(t_env *env, char *expand_str)
{
    int i;
    int double_quote;
    
    i = 0;
    double_quote = 0;
    while (expand_str[i])
    {
        if (expand_str[i] == '\"')
            double_quote = !double_quote;
        if (expand_str[i] == '\'' && double_quote == 0)
            skip_single_quote(expand_str, &i);
        else
            if (expand_str[i] == '$')
                expand_and_join(env, &expand_str, &i);
        i++;
    }
    return (expand_str);
}
// char* expand_variable(t_env* env, char* input) {
//     char* pos = strchr(input, '$'); // Find the position of "$" in the input string
//     if (pos != NULL) { // If "$" is found
//         if (strcmp(pos + 1, "USER") == 0) { // Check if the variable is "USER"
//             char* user_value = find_env_value(env, "USER"); // Get the value of the "USER" variable from the linked list
//             if (user_value != NULL) { // If the "USER" variable exists in the environment
//                 char* new_str = malloc(strlen(input) + strlen(user_value) + 1); // Allocate memory for the new string
//                 strncpy(new_str, input, pos - input); // Copy the part of the input string before "$"
//                 new_str[pos - input] = '\0'; // Null-terminate the new string
//                 strcat(new_str, user_value); // Append the "USER" variable value to the new string
//                 strcat(new_str, pos + strlen("USER") + 1); // Append the part of the input string after the variable name
//                 return new_str; // Return the new string
//             }
//         }
//     }

//     return input; // If "$" is not found, or the "USER" variable does not exist in the environment, return the original string
// }
