/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:24:21 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/11 18:26:51 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

# include "struct.h"

/*UTILS*/
int				ft_isspace(char c);
int				empty_line(char *line);
void			skip_single_quote(char *str, int *i);
char			*pass_white_space(char *s);
char			*my_strncpy(char *dest, const char *src, size_t n);
char			*ft_strndup(const char *s, size_t n);
t_type			type_of_redir(t_type type);
int				is_redir(t_type type);
int				is_word(t_type type);
int				is_pipe(t_type type);
int				count_pipes_token(t_token *tokens, int n_tokens);
void			print_env_list(t_env *env);
int     cmd_size(t_parse_list *parse_list);

//char	*ft_strcat(char *dest, char *src);
#endif