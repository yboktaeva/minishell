/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analyse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:53:00 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/04 18:56:25 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

t_token *tokenize_input(t_env *env, char *line, t_table *info)
{
    (void)env;
    t_token *tokens;
    char *expand_output;
    info->n_tokens = count_tokens(line);
    if (info->n_tokens < 0)
        return (NULL);
    tokens = malloc(sizeof(struct s_token) * info->n_tokens);
    if (!tokens)
        return (NULL);
    expand_output = expand_variable(env, line);
    printf("EXPAND: %s\n", expand_output);
    tokens = split_tokens(expand_output, tokens); /*add expand $ with envp structure*/
    //remove_quotes(tokens, n_tokens);/*code this part after expand $ sign*/
    return (tokens);
}

void    print_tokens(t_token *tokens, int n_tokens)
{
    int i;

    i = 0;
    while (i < n_tokens)
    {
        printf("Token %d: Type = %d, Value = %s\n", i, tokens[i].type, tokens[i].value);
        i++;
    }
}

// int    type_of_quotes(char *str, int type)
// {
//     int type_quote = 0;
    
//     while (*str)
//     {
//         if (*str == '\'')
//         {
//             if ((*str + 1) == '\'')
//                 type_quote = type;
//         }
//         else if (*str == '\"')
//         {
//             if ((*str + 1) == '\"')
//                 type_quote = type;
//         }
//     }
//     return (type_quote);
// }

// void    skip_single_quotes(char *s, int *i, int *j)
// {
//     if (s[*i + 1] == '\'')
//         (*i)++;
// }

// void    remove_quotes(t_token *tokens, int n_tokens)
// {
//     int i;

//     i = 0;
//     while (i < n_tokens)
//     {
//         if (tokens[i].type == WORD)
//         {
//             if (type_of_quotes(tokens[i].value, '\''))
//                 skip_single_quotes();
//             else if (type_of_quotes(tokens[i].value, '\"'))
//             {
//                 if ()
//             }
                
//         }
//     }
// }
