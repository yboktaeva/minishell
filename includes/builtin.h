/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:08:37 by yuboktae          #+#    #+#             */
/*   Updated: 2023/10/01 12:14:49 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "struct.h"

int		is_builtin(t_one_cmd *one_cmd);
void	builtin_exec(t_one_cmd *one_cmd, t_env *env,
			t_num_cmd num_of_cmd, t_table *main);
int		cmd_cd(t_one_cmd *one_cmd, t_env *env);
void	no_home_set(t_one_cmd *one_cmd, t_env *env, int *ret);
int		specific_path_home(t_env *env, char *str);
int		specific_path(t_env *env, char *str);
char	*find_path(char *str, t_env *env);
void	change_path(t_env *env);
void	print_pwd(t_env *env, char *str);
int		cmd_echo(t_one_cmd *one_cmd);
int		cmd_env(t_env *env);
int		cmd_pwd(t_one_cmd *one_cmd);
int		cmd_unset(t_one_cmd *one_cmd, t_env *env);
int		cmd_export(t_one_cmd *one_cmd, t_env *env);
int		cmd_exit(t_one_cmd *one_cmd, t_table *main);
int		export_bad_id(char *id);
int		print_export(t_env *env);
int		valid_id(char *str);
void	find_exported(t_env *env, char *var_name);
t_env	*find_env_var(t_env *env, const char *name);

#endif
