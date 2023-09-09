/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:41:43 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/09 18:17:16 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

void	print_env_list(t_env *env)
{
	t_env	*head;

	head = env;
	while (head->next != NULL)
	{
		if (head->var_value != NULL)
			printf("%s=%s\n", head->var_name, head->var_value);
		head = head->next;
	}
	return ;
}

void	print_tokens(t_token *tokens, int n_tokens)
{
	int	i;

	i = 0;
	while (i < n_tokens)
	{
		printf("Tok %d: T = %d, V = %s\n", i, tokens[i].type, tokens[i].value);
		i++;
	}
}

void	print_parse_list(t_parse_list *parse_list)
{
	t_one_cmd	*cur_cmd;
	t_redir		*cur_redir;

	while (parse_list != NULL)
	{
		cur_cmd = parse_list->one_cmd;
		while (cur_cmd != NULL)
		{
			printf("%s\n", cur_cmd->str);
			cur_cmd = cur_cmd->next;
		}
		cur_redir = parse_list->input;
		while (cur_redir != NULL)
		{
			printf("T: %d, F: %s\n", cur_redir->type, cur_redir->file_name);
			cur_redir = cur_redir->next;
		}
		cur_redir = parse_list->output;
		while (cur_redir != NULL)
		{
			printf("T: %d, F: %s\n", cur_redir->type, cur_redir->file_name);
			cur_redir = cur_redir->next;
		}
		parse_list = parse_list->next;
	}
}
