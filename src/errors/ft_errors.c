/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 10:44:17 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/17 22:45:51 by yuliaboktae      ###   ########.fr       */
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
	printf("%s:", str);
	if (type == REDIR_IN)
    	perror("No such file or directory");
	else if (type == REDIR_OUT || type == APPEND)
    	perror("cannot open output file");
	return (NULL);
}
