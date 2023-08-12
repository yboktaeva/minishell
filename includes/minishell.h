/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:14:53 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/12 15:18:55 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "../libft/libft.h"

/*ENV*/
char	*get_path(char **envp);
/*LEXER_PARSER*/
char    **ft_split_quotes(char const *s, char c);
int     check_quotes(const char *s);
int     check_up(char *line);
int     ft_init(char *line,t_table *info);
int     check_input(char *line);
int     find_symbol(char c, const char *sym);
char    *add_space(char *s, const char *sym);
void    remove_empty_quotes(char *s);
void    remove_same_quotes(char *s);
t_node  *create_node(t_table *info);
t_node  *parse_helper(t_table *info);

/*TOKEN*/
void    free_token(t_token *tok);
t_type  identify_token_type(const char *line);
void    tokenize_input(const char *line, t_table *info);
/*UTILS*/
int     ft_isspace(char c);
int     empty_line(char *line);
int     ft_arrlen(char **arr);
char	*ft_strndup(const char *s, size_t n);
#endif