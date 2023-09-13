/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:30:10 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/13 15:32:39 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdlib.h>

// static int  if_is_heredoc(t_redir *input);

// t_here_doc    *open_heredoc(t_parse_list *parsing_list)
// {
//     t_here_doc *here_doc;

//     here_doc = malloc(sizeof(t_here_doc));
//     if (!here_doc)
//     {
// 		perror("Malloc failure in duplicate envp");
// 		return (NULL);
// 	}
//     here_doc->read = 0;
//     here_doc->next = NULL;
//     while (parsing_list)
//     {
//         if (if_is_heredoc(parsing_list->input))
//     }
//     return (here_doc);
// }

// static int  if_is_heredoc(t_redir *input)
// {
//     if (input->type == HEREDOC)
//         return (1);
//     return (0);   
// }