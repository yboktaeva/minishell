/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:14:16 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/08 18:15:24 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "struct.h"
# include "../libft/libft.h"

/*EXEC*/
void			cmd_execution(t_parse_list *parse_list, t_env *env);
void			ft_free_str_array(char **str);
char			**ft_split_ignore_spaces(const char *s, char c);
char			*get_executable_path(const char *cmd, const char *path);
char			*ft_strjoin_free(char *s1, char const *s2, int free_s1);
char			**prepare_exec_args(int argc, char **argv, \
				const char *executable_path);
int				one_cmd_exec(const char *path, \
				char **const argv, char **const envp);
int				two_cmds_exec(const char *cmd1, const char *cmd2, char **const envp, const char *input_file, const char *output_file);
#endif