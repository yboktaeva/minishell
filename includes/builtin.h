/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:08:37 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/14 00:09:40 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "struct.h"

/*BUILTINS*/
int				is_builtin(t_one_cmd *one_cmd);
void			builtin_exec(t_one_cmd *one_cmd, t_env *env, t_num_cmd num_of_cmd);
char			*print_path(char *str, char **envp);
int				pwd_oldpwd(t_table *info);
int				cmd_cd(t_table *info, char *arg);
int				cmd_echo(t_one_cmd *one_cmd);
/*int			cmd_echo(t_table *info, char **argv);*/
/*int			cmd_env(t_table *info);*/
int				cmd_env(t_env *env);
int				cmd_pwd(t_one_cmd *one_cmd);

#endif