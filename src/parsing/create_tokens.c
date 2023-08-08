/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:59:20 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/08 19:50:47 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_token *create_token(t_type type, char *value)
{
    t_token *tok;

    tok = malloc(sizeof(t_token));
    tok->type = type;
    tok->value = ft_strdup(value);
    return (tok);
}

void    free_token(t_token *tok)
{
    free(tok->value);
    free(tok);
}

// void tokenize_cmd(const char *command, t_token **tokens)
// {
//     const char *start;
//     const char *end;
//     int count;
//     int len;
    
//     count = 0;
//     start = command;
//     while (*start)
//     {
//         if (*start == ' ')
//             start++;
//         if (*start == '<')
//         {
//             if (*(start + 1) == '<')
//                 (*tokens)->type = LESSLESS;
//             else
//                 (*tokens)->type = LESS;
//         }
//         else if (*start == '>')
//         {
//             if (*(start + 1) == '>')
//                 (*tokens)->type = GREATGREAT;
//             else
//                 (*tokens)->type = GREAT;
//         }
//         else if (*start == '|')
//             (*tokens)->type = PIPE;
//         else if (*start == '\'')
//             (*tokens)->type = S_QUOT;
//         else if (*start == '\"')
//             (*tokens)->type = D_QUOT;
//         else if (*start == '-')
//             (*tokens)->type = OPTION;
//         else
//             (*tokens)->type = WORD;
//         end = start;
//         while (*end && *end != ' ')
//             ++end;
//         len = end - start;
//         if (len >= MAX_TOKEN_LENGTH)
//         {
//             printf("Error: Token length exceeds max limit\n");
//             exit(1);
//         }
//         char value[MAX_TOKEN_LENGTH];
//         ft_strncpy(value, start, len);
//         value[len] = '\0';
//         tokens[count] = create_token((*tokens)->type, value);
//         ++count;
//         start = end;
//     }
// }