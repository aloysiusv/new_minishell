/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:50:54 by lrandria          #+#    #+#             */
/*   Updated: 2021/06/25 15:50:54 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_front(t_list **alst, void (*del)(void*))
{
	t_list			*tmp;

	tmp = *alst;
	*alst = (*alst)->next;
	ft_lstdelone(tmp, del);
}
