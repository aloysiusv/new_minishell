/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes_delete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:00:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/29 00:45:58 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_node *node)
{
	if (node->word)
	{
		free(node->word);
		node->word = NULL;
	}
	if (node)
	{
		free(node);
		node = NULL;
	}
}

/* /!\ CHANTIER DANGEREUX /!\ */
static void    delete_edges(t_node **head, int mode)
{
	t_node	*tmp;
	t_node	*tail;

	if (mode == FIRST)
	{
		tmp = *head;
		if ((*head)->next)
			*head = (*head)->next;
		(*head)->prev = NULL;
		delete_node(tmp);
		printf("first node deleted\n");
	}
	else
	{
		tail = get_lst_tail(*head);
		tmp = tail;
		tail = tail->prev;
		tail->next = NULL;
		delete_node(tmp);
		printf("last node deleted\n");
	}
	
}
/* /!\ CHANTIER DANGEREUX /!\ */
void	delete_specific_node(t_node **head, t_node *to_delete)
{
	t_node	*iterator;
	t_node	*tail;
	t_node	*tmp;

	tail = NULL;
	iterator = *head;
	if (ft_lstsize_2(iterator) > 1)
		tail = get_lst_tail(*head);
	if (iterator == to_delete)
		delete_edges(head, HEAD);
	else if (tail == to_delete)
		delete_edges(head, TAIL);
	else
		while (iterator)
		{
			if (iterator->next == to_delete)
			{
				tmp = iterator->next;
				iterator->next = iterator->next->next;
				iterator->next->next->prev = iterator;
				delete_node(tmp);
				printf("middle node deleted\n");
				return ;
			}
		iterator = iterator->next;
		}
}
