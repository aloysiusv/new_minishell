/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 23:45:23 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/29 00:57:14 by lrandria         ###   ########.fr       */
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

void			delete_useless_tokens(t_node **tokens)
{
	t_node	*tmp;
	t_node	*iterator;

	if (!*tokens)
		return ;
	iterator = *tokens;
	while (iterator)
	{
		printf("iterator is => [%s]\n", iterator->word);
		if (iterator->type == USELESS)
		{
			tmp = iterator;
			if (tmp->prev && tmp->next)
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				// tmp->prev = NULL;
				// tmp->next = NULL;
			}
			else if (tmp->prev && !tmp->next)
				tmp->prev->next = NULL;
			else if (!tmp->prev && tmp->next)
				tmp->next->prev = NULL;
			iterator = iterator->next;
			printf("deleting => [%s]\n", tmp->word);
			delete_node(tmp);
		}
		iterator = iterator->next;
	}
	printf("NEW TOKEN LIST IS: \n");
	t_node *ite = *tokens;
	while (ite)
	{
		printf("[%s]	=> in_squotes [%d] || in_dquotes [%d] || type [%d]\n",
			ite->word, ite->in_squotes,
				ite->in_dquotes, ite->type);
		ite = ite->next;
	}
	printf("END\n");
}
