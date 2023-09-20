/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 10:44:17 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/20 17:26:53 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stddef.h>

void	*quote_error(void)
{
	ft_putendl_fd("minishell: missing closing quote", 2);
	return (NULL);
}

void	*syntax_error(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	return (NULL);
}

void	*open_error(char *str, t_type type)
{
	if (type == REDIR_IN)
		printf("%s: No such file or directory", str);
	else if (type == REDIR_OUT || type == APPEND)
		printf("%s:cannot open output file", str);
	return (NULL);
}

void	*chdir_error(char *str)
{
	printf ("%s: No such file or directory\n", str);
	return (NULL);
}