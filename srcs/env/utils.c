/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:19:49 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 13:32:27 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	push_back_node(t_env **head, t_env *node)
{
	t_env	*curr;

	if (!*head)
	{
		*head = node;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = node;
}

void	delete_node(t_env *node)
{
	if (node)
	{
		if (node->key)
			free(node->key);
		if (node->value)
			free(node->value);
		free(node);
	}
}

void	remove_node(t_env **head, char *key)
{
	t_env	*curr;
	t_env	*tmp;

	while (*head && !ft_strcmp((*head)->key, key))
	{
		tmp = *head;
		*head = (*head)->next;
		delete_node(tmp);
	}
	curr = *head;
	while (curr && curr->next)
	{
		if (!ft_strcmp(curr->next->key, key))
		{
			tmp = curr->next;
			curr->next = tmp->next;
			delete_node(tmp);
		}
		else
			curr = curr->next;
	}
}
