/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ignore_spaces.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:00:45 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/30 10:20:56 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	count_words(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*extract_word(const char *s, char c, int *start)
{
	int		i;
	char	*word;

	i = *start;
	while (s[i] && s[i] == c)
		i++;
	*start = i;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc(i - *start + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (s[*start] && s[*start] != c)
		word[i++] = s[(*start)++];
	word[i] = '\0';
	return (word);
}

static void	free_word_array(char **words, int count)
{
	while (count > 0)
		free(words[--count]);
	free(words);
}

char	**ft_split_ignore_spaces(const char *s, char c)
{
	char	**result;
	int		word_count;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count)
	{
		result[j] = extract_word(s, c, &i);
		if (!result[j])
		{
			free_word_array(result, j);
			return (NULL);
		}
		j++;
	}
	result[j] = NULL;
	return (result);
}
