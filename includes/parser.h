/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:05:25 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/08 19:51:11 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "struct.h"

/*PARSER*/
t_parse_list	*init_parse_list(void);
t_one_cmd		*init_one_cmd(char *str);
t_redir			*init_redir_list(t_type type, char *name);
t_parse_list	*parsing_tokens(t_token *tokens, int n_tokens);
void			if_word_token(t_token *tokens, \
				t_parse_list *parse_list, int *j);
void			*if_redir_token(t_token *tokens, \
				t_parse_list *parse_list, int *j, int end);
void			*if_pipe_token(t_token *tokens, \
				t_parse_list *parse_list, int *j, int end);
void			one_cmd_node(t_one_cmd **head, t_one_cmd *node);
void			redir_node(t_redir **head, t_redir *node);
void			add_node(t_parse_list *parse_list, t_parse_list *node);
void			print_parse_list(t_parse_list *parse_list);

#endif