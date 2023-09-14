/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:31:34 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/14 16:56:10 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "struct.h"

t_env   *init_env_list(char **envp);
void    set_env_list(t_env **head, char **envp);
void    get_env(t_env *head, char *str);
t_env   *add_env_node(char *str);
t_env   *copy_env(t_env *env, char *str);
char    *env_var_name(char *str);
int     env_var_name_len(char *var_name);
char    *env_var_value(t_env *head, char *key);
#endif