/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:59:20 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/21 00:11:57 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void token_quotes(char **start, char **quote_start, t_token *tokens, int *j);
void token_redirection(char **start, char **end, t_token *tokens, int *j);
void token_pipe(char **start, t_token *tokens, int *j);
void token_word(char **start, char **end, t_token *tokens, int *j);

int split_tokens(char *line, t_token *tokens)
{
    int j;
    char *start;
    char *end;
    char *quote_start;

    j = 0;
    start = line;
    quote_start = NULL;
    while (*start != '\0')
    {
        while (ft_isspace(*start))
            start++;
        if (*start == '\0')
            break ;
        if (*start == '\'' || *start == '\"')
            token_quotes(&start, &quote_start, tokens, &j);
        else if (quote_start == NULL)
        {
            if (*start == '<' || *start == '>')
                token_redirection(&start, &end, tokens, &j);
            else if (*start == '|')
                token_pipe(&start, tokens, &j);
            else
                token_word(&start, &end, tokens, &j);
        }
        start++;
    }
    return (j);
}

void token_quotes(char **start, char **quote_start, t_token *tokens, int *j)
{
    char    quote_type;
    int     len;
    
    *quote_start = *start;
    quote_type = **start;
    (*start)++;
    while (**start != quote_type && **start != '\0')
        (*start)++;
    len = *start - *quote_start;
    tokens[*j].type = WORD;
    tokens[*j].value = calloc(len, sizeof(char));
    my_strncpy(tokens[*j].value, *quote_start + 1, len - 1);
    (*j)++;
    *quote_start = NULL;
}

void token_redirection(char **start, char **end, t_token *tokens, int *j)
{
    int len;

    len = 1;
    *end = *start;
    if (**end == '<')
    {
        if ((*end)[1] == '<')
        {
            tokens[*j].type = HEREDOC;
            len += 1;
        }
        else
            tokens[*j].type = REDIR_IN;
    }
    else if (**end == '>')
    {
        if ((*end)[1] == '>')
        {
            tokens[*j].type = APPEND;
            len += 1;
        }
        else
            tokens[*j].type = REDIR_OUT;
    }
    tokens[*j].value = calloc(len + 1, sizeof(char));
    my_strncpy(tokens[*j].value, *start, len);
    (*j)++;
    (*start)++;
}

void token_pipe(char **start, t_token *tokens, int *j)
{
    char *end;
    int len;
    
    len = 0;
    end = *start;
    if (*end == '|')
    {
        tokens[*j].type = PIPE;
        len += 1;
        tokens[*j].value = calloc(len + 1, sizeof(char));
        my_strncpy(tokens[*j].value, *start, len);
        (*j)++;
    }
}

void token_word(char **start, char **end, t_token *tokens, int *j)
{
    *end = *start;
    while (**end && **end != '\'' && **end != '\"' &&
           **end != '<' && **end != '>' && **end != '|' && !ft_isspace(**end))
        (*end)++;
    tokens[*j].type = WORD;
    tokens[*j].value = calloc(*end - *start + 1, sizeof(char));
    strncpy(tokens[*j].value, *start, *end - *start);
    (*j)++;
    *start = *end;
}
