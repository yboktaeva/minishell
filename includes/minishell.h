/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:14:53 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/05 19:31:37 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "../libft/libft.h"

# define TRUE 1
# define FAULSE 0
# define SUCCES ((void *)1)

/*READLINE_INIT*/
void    *init_main_table(t_table *info, char *line, char **argv);
void    shell_loop(t_env *env, char *line, t_table *info);
/*ENV*/
t_env   *init_env_list(char **envp);
void    set_env_list(t_env **head, char **envp);
void	get_env(t_env *head, char *str);
t_env   *add_env_node(char *str);
t_env   *copy_env(t_env *env, char *str);
void    print_env_list(t_env *env);
char    *env_var_name(char *str);
int     env_var_name_len(char *var_name);
char    *env_var_value(t_env *head, char *key);
/*PARSER*/
t_parse_list    *init_parse_list(void);
t_one_cmd       *init_one_cmd(char *str);
t_redir         *init_redir_list(t_type type, char *name);
int             fill_parse_list(t_parse_list *parse_list, t_token *tokens, int n_tokens);
t_parse_list    *parsing_tokens(t_token *tokens, int n_tokens);
void            *invalid_operator(t_token *tokens, int *j);
void            if_word_token(t_token *tokens, t_parse_list *parse_list, int *j);
void            *if_redir_token(t_token *tokens, t_parse_list *parse_list, int *j, int end);
void            *if_pipe_token(t_token *tokens, t_parse_list *parse_list, int *j, int end);
void            one_cmd_node(t_one_cmd **head, t_one_cmd *node);
void            redir_node(t_redir **head, t_redir *node);
void            add_node(t_parse_list *parse_list, t_parse_list *node);
void            print_parse_list(t_parse_list *parse_list);
/*LEXER_TOKEN*/
int     count_quotes(char *s);
int     count_tokens(char *line);
void    token_quotes(char **start, char **quote_start, t_token *tokens, int *j);
void    token_redirection(char **start, char **end, t_token *tokens, int *j);
void    token_pipe(char **start, t_token *tokens, int *j);
void    token_word(char **start, char **end, t_token *tokens, int *j);
void    print_tokens(t_token *tokens, int n_tokens);
t_token *split_tokens(char *line, t_token *tokens);
t_token *tokenize_input(t_env *env, char *line, t_table *info);
char    *if_dollar(t_env *env, char *expand_str);
void    join_before_and_after(t_env *env, char **str, int *i);
char    *find_var_value(t_env *env, char *str, int *i);
void    *expand_word_token(t_env *env, t_token *tokens, t_table *info);
void    delete_quotes(t_token *tokens, int n_tokens);
void    get_rid_quotes(char *value);
void    if_quotes_in_quotes(char *str, char quote_flag, int *i, int *j);
int     if_quotes_closed(char *str);
/*EXEC*/
void	ft_free_str_array(char **str);
char	**ft_split_ignore_spaces(const char *s, char c);
char	*get_executable_path(const char *cmd, const char *path);
char	*ft_strjoin_free(char *s1, char const *s2, int free_s1);
char    **prepare_exec_args(int argc, char **argv, const char *executable_path);
int     one_cmd_exec(const char *path, char **const argv, char **const envp);
int     two_cmds_exec(const char *cmd1, const char *cmd2, char **const envp, const char *input_file, const char *output_file);
/*BUILTINS*/
char    *print_path(char *str, char **envp);
int     pwd_oldpwd(t_table *info);
int     cmd_cd(t_table *info, char *arg);
int     cmd_echo(t_table *info, char **argv);
int     cmd_env(t_table *info);
int     cmd_pwd(void);
/*ERRORS*/
void    *quote_error(void);
void    *syntax_error(char *str);
/*DESTRUCTOR*/
void    free_all(char *line, t_token *tokens, int n_tokens);
void    free_token(t_token *tokens, int n_tokens);
void    free_one_cmd_list(t_one_cmd *head);
void    free_redirect_list(t_redir *head);
void    free_parse_list(t_parse_list *head);
void    free_env(t_env **head);
/*UTILS*/
int     ft_isspace(char c);
int     empty_line(char *line);
void	skip_single_quote(char *str, int *i);
char	*pass_white_space(char *s);
char    *my_strncpy(char *dest, const char *src, size_t n);
char	*ft_strndup(const char *s, size_t n);
t_type  type_of_redir(t_type type);
int     is_redir(t_type type);
int     is_word(t_type type);
int     is_pipe(t_type type);
int     count_pipes_token(t_token *tokens, int n_tokens);

#endif