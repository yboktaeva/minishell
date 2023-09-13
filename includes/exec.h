/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:14:16 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/13 23:05:36 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "struct.h"
# include "../libft/libft.h"

void    create_args(t_parse_list *parse_list, t_arg *arg);
int open_input(t_redir *input, int *fd_in);
int open_output(t_redir *output, int *fd_out);
void    handle_redirections(t_parse_list *parse_list, int *fd_in, int *fd_out);
void    cmd_execution(t_parse_list *parse_list, t_env *env, t_arg *arg);
void    ft_free_str_array(char **str);
char    **ft_split_ignore_spaces(const char *s, char c);
char    *get_executable_path(const char *cmd, const char *path);
char    *ft_strjoin_free(char *s1, char const *s2, int free_s1);
int     one_cmd_exec(t_parse_list *s, t_arg *arg);
char    *get_path_from_envp(t_arg *arg);
int     two_cmds_exec(t_parse_list *parse_list, t_arg *arg);
t_here_doc    *open_heredoc(t_parse_list *parsing_list);
#endif