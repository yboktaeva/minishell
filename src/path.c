/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:46:39 by yuboktae          #+#    #+#             */
/*   Updated: 2023/07/21 18:20:04 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/struct.h"
#include <stddef.h>

// static char	*get_path(char **envp)
// {
// 	if (!envp || !(*envp))
// 		return (NULL);
// 	while (*envp)
// 	{
// 		if (ft_strncmp("PATH=", *envp, 5) == 0)
// 			return (*envp + 5);
// 		envp++;
// 	}
// 	return (NULL);
// }