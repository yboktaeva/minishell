/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:14:53 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/07 11:13:26 by yuboktae         ###   ########.fr       */
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
int     ft_init(char **cmds, char *line);
int     check_input(char *line);
int     find_symbol(char c, const char *sym);
char    *add_space(char *s, const char *sym);
void    remove_empty_quotes(char *s);
void    remove_same_quotes(char *s);
/*TOKEN*/
void    free_token(t_token *tok);
t_token *create_token(t_type type, char *value);
/*UTILS*/
int     ft_isspace(char c);
int     empty_line(char *line);

#endif