/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:02:36 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/25 16:12:20 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new;

	if (!s)
		return (NULL);
	i = 0;
	while (s && s[i])
		i++;
	if (start > i)
		len = 0;
	if (len > i - start)
		len = i - start;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

/*#include <stdio.h>
  int	main()
  {
  char *s = "Lorem ipsum dolor sit amet consectetur adipiscing elit";
  unsigned int start = 6;
  size_t len = 10;

  char *ret = ft_substr(s, start, len);
  printf("%s\n", ret);
  free(ret);
  }
*/
