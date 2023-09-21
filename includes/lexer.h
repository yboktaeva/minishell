/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:55:34 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/21 14:26:22 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "struct.h"
/*ENV*/
t_env   *init_env_list(char **envp);
/*LEXER*/
int		count_quotes(char *s);
int		count_tokens(char *line);
void	init_var_count_tokens(char *line, int *count, char **start, \
			char **quote_start);
void	check_and_handle_redir(char **curr, char operator);
int		check_and_handle_quotes(char **start, char **quote_start, int *count);
void	token_quotes(char **start, char **quote_start, \
			t_token *tokens, int *j);
void	token_redirection(char **start, char **end, \
			t_token *tokens, int *j);
void	token_pipe(char **start, t_token *tokens, int *j);
void	token_word(char **start, char **end, t_token *tokens, int *j);
void			print_tokens(t_token *tokens, int n_tokens);
t_token	*split_tokens(char *line, t_token *tokens);
t_token	*tokenize_input(t_env *env, char *line, t_table *info);
char	*if_dollar(t_env *env, char *expand_str);
int		dollar_sign(char *str);
void	join_before_and_after(t_env *env, char **str, int *i);
char	*find_var_value(t_env *env, char *str, int *i);
void	*expand_word_token(t_env *env, t_token *tokens, t_table *info);
void	delete_quotes(t_token *tokens, int n_tokens);
void	get_rid_quotes(char *value);
void	if_quotes_in_quotes(char *str, char quote_flag, int *i, int *j);
int		if_quotes_closed(char *str);

#endif