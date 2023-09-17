/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:14:53 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/17 22:42:52 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"

/*READLINE_INIT*/
void	*init_execve_args(t_arg *arg, t_env *env);
void	*init_main_table(t_table *info, char *line, char **envp);
void	shell_loop(t_env *env, char *line, t_table *info);
/*SIGNAL*/
void    default_sigint(int sig);
void    sig_here_doc(int sig);
void    sig_parent(int sig);
void    handle_sig(int state);
/*ERRORS*/
void	*quote_error(void);
void	*syntax_error(char *str);
void	*open_error(char *str, t_type type);
/*DESTRUCTOR*/
void	free_all(t_token *tokens, int n_tokens, \
		t_parse_list *parse_list);
void	free_token(t_token *tokens, int n_tokens);
void	free_one_cmd_list(t_one_cmd *head);
void	free_redirect_list(t_redir *head);
void	free_parse_list(t_parse_list *head);
void	free_env(t_env **head);
#endif
