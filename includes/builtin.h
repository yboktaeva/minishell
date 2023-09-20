/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:08:37 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/20 16:50:11 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "struct.h"

int     is_builtin(t_one_cmd *one_cmd);
void    builtin_exec(t_one_cmd *one_cmd, t_env *env, t_table *info, t_num_cmd num_of_cmd);
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
int     export_bad_id(char *id);
int     str_check(char *str1, char *str2);
int     valid_id(char *str);
int     char_check(char *str, char c);

#endif