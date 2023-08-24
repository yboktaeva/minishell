/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:43:47 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/24 18:35:25 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    remove_quotes(t_token *tokens, int n_tokens);
void    expand_quoted(t_token *tokens);
int     type_of_quotes(char *s, int type);
void    skip_single_quotes(char *s, int *i, int *j);

int     lexer_shell()
{
    
}
void    remove_quotes(t_token *tokens, int n_tokens)
{
    int i;

    i = 0;
    while (i < n_tokens)
    {
        if (tokens[i].type == WORD)
        {
            if (type_of_quotes(tokens[i].value, '\''))
                skip_single_quotes();
            else if (type_of_quotes(tokens[i].value, '\"'))
            {
                if ()
            }
                
        }
    }
}

void    expand_quoted(t_token *tokens)
{
    char    *expand_str;
}

int    type_of_quotes(char *str, int type)
{
    int type_quote = 0;
    
    while (*str)
    {
        if (*str == '\'')
        {
            if ((*str + 1) == '\'')
                type_quote = type;
        }
        else if (*str == '\"')
        {
            if ((*str + 1) == '\"')
                type_quote = type;
        }
    }
    return (type_quote);
}

void    skip_single_quotes(char *s, int *i, int *j)
{
    if (s[*i + 1] == '\'')
        (*i)++;
}