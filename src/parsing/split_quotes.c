/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:27:53 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/25 18:00:56 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stddef.h>

static int	word_count(char const *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			nb++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nb);
}

static int	len_word(char const *s, char c)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
		}
		i++;
	}
	return (i);
}

static char	*word(char const *s, char c)
{
	int		i;
	char	quote;
	char	*word;

	i = 0;
	word = (char *)malloc(sizeof(char) * (len_word(s, c) + 1));
	if (!word)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
			{
				word[i - 1] = s[i];
				i++;
			}
		}
		else
		{
			word[i] = s[i];
			i++;
		}
	}
	word[i] = '\0';
	return (word);
}

static char	*free_arr(char **arr, int i)
{
	while (i > 0)
	{
		free (arr[i - 1]);
		i--;
	}
	free (arr);
	return (NULL);
}

char	**ft_split_quotes(char const *s, char c)
{
	int		i;
	char	**arr;

	i = 0;
	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!arr)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			arr[i] = word(s, c);
			if (!arr[i])
				return (free_arr(arr, i), NULL);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	arr[i] = NULL;
	return (arr);
}
