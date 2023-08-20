/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:14:53 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/21 00:11:37 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "../libft/libft.h"

# define TRUE 1
# define FAULSE 0

/*READ_LINE*/
char    *ft_readline(char *prompt);
int     shell_loop(char *line,t_table *info);
/*ENV*/
char	*get_path(char **envp);
/*LEXER_PARSER*/
char    **ft_split_quotes(char const *s, char c);
int     check_quotes(char *s);
int     check_up(char *line);
int     check_input(char *line);
int     find_symbol(char c, const char *sym);
void    remove_empty_quotes(char *s);
void    remove_same_quotes(char *s);
t_node  *create_node(t_table *info);
t_node  *parse_helper(t_table *info);
/*TOKEN*/
void    token_quotes(char **start, char **quote_start, t_token *tokens, int *j);
void    token_redirection(char **start, char **end, t_token *tokens, int *j);
void    token_pipe(char **start, t_token *tokens, int *j);
void    token_word(char **start, char **end, t_token *tokens, int *j);
int     split_tokens(char *line, t_token *tokens);
/*EXEC*/
void	ft_free_str_array(char **str);
char	**ft_split_ignore_spaces(const char *s, char c);
char	*get_executable_path(const char *cmd, const char *path);
char	*ft_strjoin_free(char *s1, char const *s2, int free_s1);
char    **prepare_exec_args(int argc, char **argv, const char *executable_path);
int     one_cmd_exec(const char *path, char **const argv, char **const envp);
int     two_cmds_exec(const char *cmd1, const char *cmd2, char **const envp, const char *input_file, const char *output_file);
/*BUILTINS*/
int     is_biltin(); /*simple cmd, t_env *env*/
int     builtin_echo();
int     builtin_env();
int     builtin_export();
int     builtin_pwd();
int     builtin_unset();
int     builtin_exit();
int     builtin_cd();
/*ERRORS*/
void    *quote_error(void);
void    *syntax_error(void);
/*DESTRUCTOR*/
void    free_all(char *line, t_token *tokens, t_tree *parsing);
void    free_token(t_table *info);
void    free_parse_tree();
/*UTILS*/
int     ft_isspace(char c);
int     empty_line(char *line);
char    *my_strncpy(char *dest, const char *src, size_t n);
char	*ft_strndup(const char *s, size_t n);
#endif