/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:49:17 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/25 15:27:31 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stddef.h>
#include <stdlib.h>

static char	*get_line(char *buf)
{
	char	*line;
	int		i;

	i = 0;
	while (buf && buf[i] && buf[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (free(line), NULL);
	i = 0;
	while (buf && buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf && buf[i] && buf[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*line_read(char *stash, int fd)
{
	int		n_bytes;
	char	*temp;
	char	*buf;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (free(buf), NULL);
	n_bytes = 1;
	while (n_bytes > 0)
	{
		n_bytes = read(fd, buf, BUFFER_SIZE);
		if (n_bytes == -1)
			return (free(buf), NULL);
		buf[n_bytes] = 0;
		temp = stash;
		stash = ft_strjoin_gnl(temp, buf);
		free(temp);
		if (stash[n_bytes] == '\n')
			break ;
	}
	free(buf);
	return (stash);
}

static char	*left(char *buf)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (buf && buf[i] && buf[i] != '\n')
		i++;
	line = malloc((ft_strlen(buf) - i + 1) * sizeof(char));
	if (!line)
		return (free(line), NULL);
	j = 0;
	while (buf && buf[i])
		line[j++] = buf[++i];
	line[j] = '\0';
	free (buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = line_read(stash, fd);
	if (ft_strlen(stash) == 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = get_line(stash);
	stash = left(stash);
	return (line);
}

// int main(void)
// {
// 	int fd;
// 	char *line;

// 	fd = open("trip/files/42_with_nl", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		if (line == NULL)
// 			break ;
// 	}
// }