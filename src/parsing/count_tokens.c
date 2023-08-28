/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:32:08 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/28 20:15:08 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
static int count_redirection(char **start);
static int count_quotes_token(char **start, char **quote_start);
static int count_pipe(char **start);
static int count_word(char **start);

// int count_tokens(char *line)
// {
//     int     count;
//     char    *start;
//     char    *end;

//     count = 0;
//     start = line;
//     while (start && *start != '\0')
//     {
//         start = pass_white_space(start);
//         if (*start == '\0')
//             break ;
//         if (*start == '<' || *start == '>')
//             count_redir(&start, &end, &count);
//         else if (*start == '\'' || *start == '\"')
//             count_quoted_token(&start, &end, &count);
//         else if (*start == '|')
//             count_pipes(&start, &end, &count);
//         else
//             count_word(&start, &end, &count);
//         //start = end;
//     }
//     return (count);
// }

// static int count_redir(char **start, char **end, int *count)
// {
//     if (**start == '<' || **start == '>')
//     {
//         (*count)++;
//         (*end) = (*start);
//         (*start)++;
//         if (**start == '<' || **start == '>')
//             (*end)++;
//     }
//     (*start) = (*end) + 1;
//     return(0);
// }

// static int count_quoted_token(char **start, char **end, int *count)
// {
//     char    quote;
//     quote = **start;
//     (*end) = (*start);
//     (*count)++;
//     (*start)++;
//     if (check_closed_quotes(*end) == -1)
//         return (-1);
//     (*end)++;
//     (*start) = (*end) + 1;
//     return (0);
// }

// static int count_pipes(char **start, char **end, int *count)
// {
//     if (**start == '|')
//     {
//         (*count)++;
//         (*end) = (*start);
//         (*start)++;
//     }
//     (*start) = (*end) + 1;
//     return (0);
// }

// static int count_word(char **start, char **end, int *count)
// {
//     while (ft_isspace(**start))
//         (*start)++;
//     if (**start == '\0')
//         return (0);
//     (*count)++;
//     (*end) = (*start);
//     while (**end && **end != '\'' && **end != '\"' &&
//            **end != '<' && **end != '>' && **end != '|' && !ft_isspace(**end))
//         (*end)++;
//     (*start) = (*end);
//     return (1); 
// }

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
            if (check_closed_quotes(start) != 0)
                return -1;  // Return -1 in case of error
            else
                count += count_quotes_token(&start, &quote_start);
        }
        else if (quote_start == NULL)
        {
            if (*start == '<' || *start == '>')
                count += count_redirection(&start);
            else if (*start == '|')
                count += count_pipe(&start);
            else
                count += count_word(&start);
        }
        start++;
    }
    return count;
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
    return count;
}

static int count_pipe(char **start)
{
    int count = 0;
    char *current = *start;

    if (*current && *current == '|')
        count++;
    *start = current;
    return count;
}
static int count_redirection(char **start)
{
    int count = 0;
    char *current = *start;

    while (*current && (*current == '<' || *current == '>'))
        current++;
    if (count == 1 && *current && (*current == '<' || *current == '>'))
        current++;
    count++;
    *start = current;
    return count;
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
    return count;
}
