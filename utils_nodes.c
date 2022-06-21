/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:39:17 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/21 03:34:31 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// size_t	ft_lstsize(t_lst *lst)
// {
// 	size_t	size;
//     t_node  *iterator;

// 	if (!lst->head)
// 		return (0);
//     iterator = lst->head;
// 	size = 0;
// 	while (iterator)
// 	{
// 		iterator = iterator->next;
// 		size++;
// 	}
// 	return (size);
// }

void	delete_node(t_node *node)
{
	if (node->word)
	{
		printf("word[%s] is freed\n", node->word);
		free(node->word);
	}
	if (node)
		free(node);
}

void	delete_lst(t_node **head)
{
	t_node	*tmp;
	// size_t	size;

	// size = ft_lstsize(lst);
	if (!(*head))
		return ;
	// printf("size = [%zu]\n", size);
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		delete_node(tmp);
		// size--;
	}
	// free(head);
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