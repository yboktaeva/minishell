/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:30:10 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/20 11:49:44 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// static int  if_is_heredoc(t_redir *input);

// t_here_doc    *open_heredoc(t_parse_list *parse_list)
// {
//     t_here_doc *here_doc;

//     here_doc = malloc(sizeof(t_here_doc));
//     if (!here_doc)
//     {
// 		perror("Malloc failure in open heredoc");
// 		return (NULL);
// 	}
//     here_doc->read = 0;
//     here_doc->next = NULL;
//     while (parse_list)
//     {
//         if (if_is_heredoc(parse_list->input))
//     }
//     return (here_doc);
// }

// static int  if_is_heredoc(t_redir *input)
// {
//     if (input->type == HEREDOC)
//         return (1);
//     return (0);   
// }

// int write_heredoc(int *fd, char *sep)
// {
//     char    *str;

//     while (1)
//     {
//         str = readline(">");
//         if (!str)
//             break ;
//         else
//         {
//             if (ft_strncmp(sep, str, ft_strlen(sep + 1)) == 0)
//                 break ;
//             // if (str[0] != '\0')
//             write(fd[1], str, ft_strlen(str));
//             write(fd[1], "\n", 1);
//             free(str);
//         }
//     }
//     free(str);
//     close(fd[0]);
//     close(fd[1]);
//     return (0);
// }

// int open_tmp_file(t_redir *input)
// {
//     int fd;
    
//     fd = (input->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
//     if (fd == -1)
//         perror("");
// }