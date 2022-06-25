/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:39:17 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/25 10:29:29 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node_var(t_env *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	if (node)
		free(node);
}

void	delete_specific_node_var(t_env **head, char *key)
{
	t_env	*iterator;

	iterator = *head;
	while (iterator)
	{
		if (ft_strncmp(iterator->key, key, ft_strlen(key)) == 0)
		{
			if (iterator->prev && iterator->next)
			{
				iterator->prev->next = iterator->next;
				iterator->next->prev = iterator->prev;
			}
			else if (iterator->prev && !iterator->next)
				iterator->prev->next = NULL;
			delete_node_var(iterator);
			return ;
		}
		iterator = iterator->next;
	}
}

void	delete_lst_var(t_env **head)
{
	t_env	*tmp;

	if (!(*head))
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		delete_node_var(tmp);
		tmp = NULL;
	}
}

t_env	*create_node_var(char **keyvalue)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(keyvalue[0]);
    if (!new->key)
		return (NULL);
	new->value = ft_strdup(keyvalue[1]);
	if (!new->value)
		return (free(new->key), NULL);
	new->prev = NULL;
	new->next = NULL;
	free_tab(keyvalue);
	return (new);
}

t_env	*add_bottom_node_var(char **keyvalue, t_env *current_last)
{
	t_env	*bottom;

	bottom = create_node_var(keyvalue);
	if (!bottom)
		return (NULL);
	if (current_last)
	{
		current_last->next = bottom;
		bottom->prev = current_last;
		bottom->next = NULL;
	}
	return (bottom);
}

// t_env	*add_top_node_var(char **keyvalue, t_env *current_top)
// {
// 	t_env	*top;

// 	top = create_node_var(keyvalue);
// 	if (!top)
// 		return (NULL);
// 	if (current_top)
// 	{
// 		current_top->prev = top;
// 		top->next = current_top;
// 		top->prev = NULL;
// 	}
// 	return (top);
// }
