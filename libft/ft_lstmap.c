/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:42:15 by yuboktae          #+#    #+#             */
/*   Updated: 2022/11/24 11:22:58 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst1;
	t_list	*tab;

	if (lst == NULL || f == NULL)
		return (NULL);
	lst1 = NULL;
	while (lst)
	{
		tab = ft_lstnew((*f)(lst->content));
		if (!tab)
		{
			ft_lstclear(&lst1, del);
			return (0);
		}
		ft_lstadd_back(&lst1, tab);
		lst = lst->next;
	}
	return (lst1);
}
