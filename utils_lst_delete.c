/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:00:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/29 20:51:39 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_node *node)
{
	if (node->word)
	{
		// printf("Deleting word [%s]\n", node->word);
		free(node->word);
		node->word = NULL;
	}
	if (node)
	{
		free(node);
		node = NULL;
	}
}

void	delete_lst(t_node **head)
{
	t_node	*tmp;

	if (!(*head))
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		delete_node(tmp);
		tmp = NULL;
	}
}

void	delete_useless_tokens(t_node **tokens, int type)
{
	t_node	*curr;
	t_node	*tmp;

	while (*tokens && (*tokens)->type == type)
	{
		curr = *tokens;
		*tokens = (*tokens)->next;
		delete_node(curr);
	}
	curr = *tokens;
	while (curr && curr->next)
	{
		if (curr->next->type == type)
		{
			tmp = curr->next;
			curr->next = tmp->next;
			delete_node(tmp);
		}
		else
			curr = curr->next;
	}
}
