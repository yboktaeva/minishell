/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:32:08 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/01 14:23:54 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int count_redirection(char **start);
static int count_quotes_token(char **start, char **quote_start);
static int count_pipe(char **start);
static int count_word(char **start);

int count_tokens(char *line)
{
    int count = 0;
    char *start;
    char *quote_start;

    start = line;
    quote_start = NULL;
    while (*start)
    {
        start = pass_white_space(start);
        if (*start == '\0')
            break ;
        if (*start == '\'' || *start == '\"')
        {
            if (count_quotes(start) != 0)
            {
                quote_error();
                return (-1);
            }
            else
                count += count_quotes_token(&start, &quote_start);
        }
        else if (quote_start == NULL)
        {
            if (check_operator(line) != 0)
                return (-1);
            if (*start == '<' || *start == '>')
                count += count_redirection(&start);
            else if (*start == '|')
                count += count_pipe(&start);
            else
                count += count_word(&start);
        }
        start++;
    }
    return (count);
}

static int count_quotes_token(char **start, char **quote_start)
{
    int count = 0;
    *quote_start = *start;
    char quote = **start;
    (*start)++;
    while (**start != quote && **start != '\0')
        (*start)++;
    *quote_start = NULL;
    count++;
    return (count);
}

static int count_pipe(char **start)
{
    int count = 0;
    char *current = *start;

    if (*current && *current == '|')
        count++;
    *start = current;
    return (count);
}

static int count_redirection(char **start)
{
    int count = 0;
    int len = 1;
    char *current = *start;
    if (*current == '<')
    {
        current++;
        if (*current == '<')
            len += 1;
        else
            current--;
    }
    else if (*current == '>')
    {
        current++;
        if (*current == '>')
            len += 1;
        else
            current--;
    }
    count++;
    *start = current;
    return (count);
}

static int count_word(char **start)
{
    int count = 0;
    char *current = *start;

    while (*current && *current != '\'' && *current != '\"' &&
           *current != '<' && *current != '>' && *current != '|'&& !ft_isspace(*current))
        current++;
    count++;
    *start = current - 1;
    return (count);
}
