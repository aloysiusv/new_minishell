/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:39:17 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/25 04:07:33 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node_var(t_env_var *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	if (node)
		free(node);
}

void	delete_lst_var(t_env_var **head)
{
	t_env_var	*tmp;

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

t_env_var	*create_node_var(char **keyvalue)
{
	t_env_var	*new;

	new = (t_env_var *)malloc(sizeof(t_env_var));
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

t_env_var	*add_bottom_node_var(char **keyvalue, t_env_var *current_last)
{
	t_env_var	*bottom;

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

t_env_var	*add_top_node_var(char **keyvalue, t_env_var *current_top)
{
	t_env_var	*top;

	top = create_node_var(keyvalue);
	if (!top)
		return (NULL);
	if (current_top)
	{
		current_top->prev = top;
		top->next = current_top;
		top->prev = NULL;
	}
	return (top);
}
