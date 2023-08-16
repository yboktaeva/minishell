/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:14:53 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/16 17:24:21 by yuboktae         ###   ########.fr       */
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
/*ENV*/
char	*get_path(char **envp);
/*LEXER_PARSER*/
char    **ft_split_quotes(char const *s, char c);
int     check_quotes(char *s);
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
t_type  identify_token_type(char *line);
void    tokenize_input(char *line, t_table *info);
/*EXEC*/
void	ft_free_str_array(char **str);
char	**ft_split_ignore_spaces(const char *s, char c);
char	*get_executable_path(const char *cmd, const char *path);
char	*ft_strjoin_free(char *s1, char const *s2, int free_s1);
char    **prepare_exec_args(int argc, char **argv, const char *executable_path);
int     one_cmd_exec(const char *path, char **const argv, char **const envp);
int     two_cmds_exec(const char *cmd1, const char *cmd2, char **const envp, const char *input_file, const char *output_file);
/*ERRORS*/
void    *quote_error(void);
void    *syntax_error(void);
/*UTILS*/
int     ft_isspace(char c);
int     empty_line(char *line);
int     ft_arrlen(char **arr);
char	*ft_strndup(const char *s, size_t n);
#endif