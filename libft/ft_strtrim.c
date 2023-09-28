/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:22:15 by yuboktae          #+#    #+#             */
/*   Updated: 2023/09/28 14:07:20 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*new_s;

	if (!s || !set)
		return (NULL);
	start = 0;
	while (s[start] && in_set(s[start], set))
		start++;
	end = ft_strlen(s);
	while (end > start && in_set(s[end - 1], set))
		end--;
	new_s = (char *)malloc(sizeof(*s) * (end - start + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (start < end)
		new_s[i++] = s[start++];
	new_s[i] = '\0';
	return (new_s);
}
