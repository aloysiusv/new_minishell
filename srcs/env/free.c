/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 00:48:56 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 01:31:31 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_lst_env(t_env **head)
{
	t_env	*curr;
	t_env	*tmp;

	if (!*head)
		return ;
	curr = *head;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		delete_node(tmp);
	}
	*head = NULL;
}
