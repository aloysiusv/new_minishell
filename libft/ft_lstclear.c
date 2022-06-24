/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:00:48 by lrandria          #+#    #+#             */
/*   Updated: 2021/06/10 18:12:22 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*to_del;

	if (lst == 0)
		return ;
	node = *lst;
	while (node)
	{
		to_del = node;
		node = node->next;
		if (del)
			del(to_del->content);
		free(to_del);
	}
	*lst = NULL;
}
