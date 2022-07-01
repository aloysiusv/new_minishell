/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:39:17 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/30 22:12:25 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	insert_tokens(t_node **tokens, t_node *prev, t_node **new)
{
	t_node	*iterator;

	if (!*tokens || !prev)
		return ;
	iterator = *tokens;
	while (iterator != prev)
		iterator = iterator->next;
	(*new)->next = iterator->next;
	iterator->next = *new;
}
