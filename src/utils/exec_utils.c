/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:56:18 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/11 20:53:56 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int	cmd_size(t_parse_list *parse_list)
{
	t_parse_list	*tmp;
	int				len;

	len = 0;
	tmp = parse_list;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
int	env_size(t_env *env)
{
	t_env	*tmp;
	int		len;

	len = 0;
	tmp = env;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**duplicate_envp(t_env *env)
{
	int		i;
	char	*temp_str;
	char	**cp_envp;
	t_env	*tmp;

	i = 0;
	tmp = env->next;
	cp_envp = malloc((env_size(env) + 1) * sizeof(char *));
	if (!cp_envp)
	{
		perror("Malloc failure");
		return (NULL);
	}
	while (tmp != NULL)
	{
		temp_str = ft_strjoin(tmp->var_name, "=");
		cp_envp[i] = ft_strjoin(temp_str, tmp->var_value);
		//printf("%s\n", cp_envp[i]);
		free(temp_str);
		i++;
		tmp = tmp->next;
	}
	cp_envp[i] = NULL;
	return (cp_envp);
}
