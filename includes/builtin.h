/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:08:37 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/24 01:57:50 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "struct.h"

int     is_builtin(t_one_cmd *one_cmd);
void    builtin_exec(t_one_cmd *one_cmd, t_env *env, t_num_cmd num_of_cmd);
int     cmd_cd(t_one_cmd *one_cmd,  t_env *env);
int     specific_path(t_env *env, char *str);
char	*find_path(char *str, t_env *env);
void	change_path(t_env *env);
void	print_pwd(t_env *env, char *str);
int     cmd_echo(t_one_cmd *one_cmd);
int     cmd_env(t_env *env);
int     cmd_pwd(t_one_cmd *one_cmd);
int     cmd_unset(t_one_cmd *one_cmd, t_env *env);
int     cmd_export(t_one_cmd *one_cmd, t_env *env);
void	cmd_exit(t_one_cmd *one_cmd);
int     export_bad_id(char *id);
int     print_export(t_env *env);
int     valid_id(char *str);
void    find_exported(t_env *env, char *var_name);

#endif