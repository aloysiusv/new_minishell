/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:16:32 by lrandria          #+#    #+#             */
/*   Updated: 2021/06/10 13:58:50 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*new_alst;

	if (alst == 0 || new == 0)
		return ;
	if (*alst == 0)
	{
		*alst = new;
		return ;
	}
	new_alst = *alst;
	while (new_alst->next != NULL)
		new_alst = new_alst->next;
	new_alst->next = new;
}
