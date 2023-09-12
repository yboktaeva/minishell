/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:14:53 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/12 18:44:23 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"

/*READLINE_INIT*/
void			init_execve_args(t_arg *arg, t_env *env);
void			*init_main_table(t_table *info, char *line, char **envp);
void			shell_loop(t_env *env, char *line, t_table *info);
/*ERRORS*/
void			*quote_error(void);
void			*syntax_error(char *str);
/*DESTRUCTOR*/
void			free_all(t_token *tokens, int n_tokens, \
				t_parse_list *parse_list);
void			free_token(t_token *tokens, int n_tokens);
void			free_one_cmd_list(t_one_cmd *head);
void			free_redirect_list(t_redir *head);
void			free_parse_list(t_parse_list *head);
void			free_env(t_env **head);
#endif
