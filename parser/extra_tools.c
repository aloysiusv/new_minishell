/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 23:45:23 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/29 02:48:58 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_word_size(t_node *current, int type)
{
	size_t	size;
	t_node	*iterator;

	size = 0;
	iterator = current;
	while (iterator && iterator->type == type)
	{
		iterator = iterator->next;
		size++;
	}
	return (size);
}

char			*create_word(t_node *current, int type)
{
	size_t	i;
	size_t	size;
	char	*word;
	t_node	*iterator;

	size = get_word_size(current, type);
	word = (char *)malloc(sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	iterator = current;
	i = 0;
	while (i < size)
	{
		word[i] = iterator->charac;
		if (iterator)
			iterator = iterator->next;
		i++;
	}
	word[i] = '\0';
	return (word);
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
		curr = curr->next;
	}
}