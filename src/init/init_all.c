/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:57:27 by yuliaboktae       #+#    #+#             */
/*   Updated: 2023/09/28 14:47:10 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

void	*init_main_table(t_table *main)
{
	main->env = NULL;
	main->arg = NULL;
	main->tokens = NULL;
	main->parse_list = NULL;
	main->here_doc = NULL;
	main->n_tokens = 0;
	main->cmd_info = NULL;
	return (SUCCES);
}

void	*init_execve_args(t_arg *arg, t_env *env)
{
	arg->argv = NULL;
	arg->n_args = 0;
	arg->envp = duplicate_envp(env);
	return (SUCCES);
}

t_parse_list	*init_parse_list(void)
{
	t_parse_list	*new;

	new = malloc(sizeof(t_parse_list));
	if (!new)
		return (NULL);
	new->one_cmd = NULL;
	new->input = NULL;
	new->output = NULL;
	new->next = NULL;
	return (new);
}

t_one_cmd	*init_one_cmd(char *str)
{
	t_one_cmd	*new;

	new = malloc(sizeof(t_one_cmd));
	if (!new)
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}

t_redir	*init_redir_list(t_type type, char *name)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (new);
	new->type = type;
	new->file_name = name;
	new->next = NULL;
	return (new);
}
