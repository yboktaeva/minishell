/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:25:36 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/23 14:43:42 by yuboktae         ###   ########.fr       */
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

int	check_input(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\' || line[i] == ';' || (line[i] == '&' && line[i + 1] == '&'))
			return (-1);
		i++;
	}
	return (0);
}

int  check_up(char *line)
{
    if (check_quotes(line) < 0)
    {
        quote_error();
        return (-1);
    }
    if (check_input(line) < 0)
    {
        //syntax_error();
        return (-1);
    }
    return (0);
}

int	find_symbol(char c, const char *sym)
{
	while (*sym)
	{
		if (c == *sym)
			return (1);
		sym++;
	}
	return (0);
}

// char	*add_space(char *s, const char *sym)
// {
// 	char	*str;
// 	int		len;
// 	int		new_len;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	len = ft_strlen(s);
// 	new_len = len;
// 	while (i < len)
// 	{
// 		if (i > 0 && i < len)
// 		{
// 			if (((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' && s[i
// 						+ 1] == '>') || (s[i] == '&' && s[i + 1] == '&')
// 					|| (s[i] == '|' && s[i + 1] == '|')))
// 			{
// 				if (!ft_isspace(s[i - 1]) || !ft_isspace(s[i + 2]))
// 					new_len += 1;
// 				else if (!ft_isspace(s[i - 1]) && !ft_isspace(s[i + 2]))
// 					new_len += 2;
// 			}
// 			else if (find_symbol(s[i], sym))
// 			{
// 				if (!ft_isspace(s[i - 1]) || !ft_isspace(s[i + 1]))
// 					new_len += 1;
// 				else if (!ft_isspace(s[i - 1]) && !ft_isspace(s[i + 1]))
// 					new_len += 2;
// 			}
// 		}
// 		i++;
// 	}
// 	str = (char *)malloc(sizeof(char) * new_len + 1);
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (i < len)
// 	{
// 		if (i > 0 && i < len)
// 		{
// 			if (((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' && s[i
// 						+ 1] == '>') || (s[i] == '&' && s[i + 1] == '&')
// 					|| (s[i] == '|' && s[i + 1] == '|')))
// 			{
// 				if ((!ft_isspace(s[i - 1]) && !ft_isspace(s[i + 2]))
// 					|| !ft_isspace(s[i - 1]) || !ft_isspace(s[i + 2]))
// 				{
// 					if (i != 0)
// 						str[j++] = ' ';
// 					str[j++] = s[i];
// 					str[j++] = s[i + 1];
// 					if (i != len - 2)
// 						str[j++] = ' ';
// 				}
// 				else
// 				{
// 					str[j++] = s[i];
// 					str[j++] = s[i + 1];
// 				}
// 				i++;
// 			}
// 			else if (find_symbol(s[i], sym))
// 			{
// 				if ((!ft_isspace(s[i - 1]) && !ft_isspace(s[i + 1]))
// 					|| !ft_isspace(s[i - 1]) || !ft_isspace(s[i + 1]))
// 				{
// 					if (i != 0)
// 						str[j++] = ' ';
// 					str[j++] = s[i];
// 					if (i != len - 1)
// 						str[j++] = ' ';
// 				}
// 				else
// 					str[j++] = s[i];
// 			}
// 			else
// 				str[j++] = s[i];
// 		}
// 		i++;
// 	}
// 	str[j] = '\0';
// 	return (str);
// }
