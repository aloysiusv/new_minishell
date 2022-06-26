/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:39:17 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/26 00:56:18 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_lstsize_2(t_node *head)
{
	size_t	size;
    t_node  *iterator;

	if (!head)
		return (0);
    iterator = head;
	size = 0;
	while (iterator)
	{
		iterator = iterator->next;
		size++;
	}
	return (size);
}

void	delete_node(t_node *node)
{
	if (node->word)
		free(node->word);
	if (node)
		free(node);
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
		if (tmp->word)
			printf("In 'delete_lst': about to delete [%s]\n", tmp->word);
		delete_node(tmp);
		tmp = NULL;
	}
}

t_node	*create_node(char my_char, char *my_word, int my_type)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
    new->charac = '\0';
    new->word = NULL;
	if (my_char)
        new->charac = my_char;
    if (my_word)
		new->word = my_word;
    new->type = my_type;
	new->in_squotes = false;
	new->in_dquotes = false;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_node	*add_bottom_node(t_node *current_last, char value, char *word, int type)
{
	t_node	*bottom;

	bottom = create_node(value, word, type);
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