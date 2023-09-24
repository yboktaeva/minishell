/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:14:16 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/24 18:35:10 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "struct.h"

void    create_args(t_parse_list *parse_list, t_arg *arg);
int     handle_redirections(t_parse_list *parse_list, t_here_doc *here_doc, int *fd_in, int *fd_out);
void    cmd_execution(t_parse_list *parse_list, t_table *main);
void    one_builtin(t_parse_list *parse_list, t_table *main, t_cmd_info *cmd_info);
void    ft_free_str_array(char **str);
char    **ft_split_ignore_spaces(const char *s, char c);
char    *get_executable_path(const char *cmd, const char *path);
char    *ft_strjoin_free(char *s1, char const *s2, int free_s1);
int     one_cmd_exec(t_parse_list *parse_list, t_table *main, t_cmd_info *cmd_info);
char    *get_path_from_envp(t_env *env);
t_here_doc    *open_heredoc(t_parse_list *parse_list);
void    add_back_heredoc(t_here_doc *here_doc, int fd);
void    free_n_close_heredoc(t_here_doc *head, int fd);
int     multi_cmds_exec(t_parse_list *parse_list, t_table *main, t_cmd_info *cmd_info);
void    exec_comds(const char *path, t_arg *arg);
void    ft_close(int fd);
void    close_fd_cmd(t_cmd_info *cmd_info);
int     wait_all_pid(t_cmd_info *cmd_info, pid_t pid, pid_t *pids);
void    reset_cmd_info(t_cmd_info *cmd_info);
#endif