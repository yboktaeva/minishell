/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:59:35 by asekmani          #+#    #+#             */
/*   Updated: 2023/09/24 02:03:39 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_free_str_array(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*ft_strjoin_free(char *s1, char const *s2, int free_s1)
{
	size_t i;
	size_t size;
	char *res;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1) || i < ft_strlen(s2))
	{
		if (i < ft_strlen(s1))
			res[i] = s1[i];
		if (i < ft_strlen(s2))
			res[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	res[size] = '\0';
	if (free_s1)
		free(s1);
	return (res);
}