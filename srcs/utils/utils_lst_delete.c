/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:00:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 22:57:30 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_node_delete_node(t_node *node)
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

void	t_node_delete_lst(t_node **head)
{
	t_node	*tmp;
	t_node	*curr;

	if (!(*head))
		return ;
	curr = *head;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		t_node_delete_node(tmp);
	}
	*head = NULL;
}

void	t_node_delete_useless_tokens(t_node **tokens, int type)
{
	t_node	*curr;
	t_node	*tmp;

	while (*tokens && (*tokens)->type == type)
	{
		curr = *tokens;
		*tokens = (*tokens)->next;
		t_node_delete_node(curr);
	}
	curr = *tokens;
	while (curr && curr->next)
	{
		if (curr->next->type == type)
		{
			tmp = curr->next;
			curr->next = tmp->next;
			t_node_delete_node(tmp);
		}
		else
			curr = curr->next;
	}
}
