/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:14:53 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/26 16:20:46 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "../libft/libft.h"

# define TRUE 1
# define FAULSE 0

/*ENV*/
char	*get_path(char **envp);
/*LEXER_PARSER*/
char    **ft_split_quotes(char const *s, char c);
int     check_quotes(char *s);
int     check_double_quotes(char *s);
/*UTILS*/
int     ft_isspace(char c);
int     empty_line(char *line);

#endif