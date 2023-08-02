/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:27:53 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/02 19:20:13 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int word_count(char const *s, char c)
{
    int count = 0;
    int in_word = 0;
    int in_quote = 0;

    while (*s)
    {
        if (*s == '\'' || *s == '\"')
        {
            if (!in_quote)
            	in_quote = *s;
            else if (in_quote == *s)   
                in_quote = 0;
        }
        if (!in_quote && *s == c)
        {
            if (in_word)
            {
                count++;
                in_word = 0;
            }
        }
        else
            in_word = 1;
        s++;
    }
    if (in_word)
    	count++;
    return count;
}

static char	*copy_word(char const *s, char c)
{
	char	*word;
	int		len;
	
	len = 0;
	while (*s && *s == c)
		s++;
	while (*s && *s != c)
	{
		len++;
		s++;	
	}
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	s -= len;
	int i = 0;
	while (*s && *s != c)
    {
        if (*s == '\'' || *s == '\"')
		{
			if (s[0] == s[1])
            	s++;
		}
        else
            word[i++] = *s;
        s++;
    }
	word[i] = '\0';
	return (word);
}

static void	free_array(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char **ft_split_quotes(char const *s, char c)
{
    int i;
    int count;
    char **arr;
	char	quote;
	int		len;
	const char *start;
	
	count = word_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
        return NULL;
	i = 0;
	while (*s && i < count)
	{
        if (*s == '\'' || *s == '\"')
		{
            quote = *s;
            s++;
            len = 0;
            start = s;
            while (*s && *s != quote)
            {
                len++;
				s++;
			}
            s++;
            arr[i] = (char *)malloc(sizeof(char) * (len + 1));
            if (!arr[i])
            {
                free_array(arr, i);
                return NULL;
            }
			// int j = 0;
			// while (j < len)
			// {
			// 	if (start[j] != quote)
			// 		arr[i][j] = start[j];
			// 	j++;
			// }
            ft_strlcpy(arr[i], start, len + 1);
            arr[i][len] = '\0';
        }
		else
		{
			arr[i] = copy_word(s, c);
			if (!arr[i])
			{
				free_array(arr, i);
					return (NULL);
			}
			s += ft_strlen(arr[i]);
		}
		i++;
		while (*s && *s != c)
			s++;
	}
	arr[i] = NULL;
	return (arr);
}