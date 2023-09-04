/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:25:36 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/04 15:30:34 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}

// void	*invalid_operator(char *line, char *check)
// {
// 	if (ft_strcmp(line, check) == 0)
// 		return (syntax_error(check));
// 	else
// 		return (SUCCES);
// }

// int	check_operator(char *line)
// {
// 	while (line)
// 	{
// 		if (!invalid_operator(line, "&") || !invalid_operator(line, "&&")
// 			|| !invalid_operator(line, "||") || !invalid_operator(line, ";")
// 			|| !invalid_operator(line, "\\"))
// 			return (-1);
// 		line++;
// 	}
// 	return (0);
// }