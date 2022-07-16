/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:10:27 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 09:05:45 by wmachrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	hrdoc_get_word_size(t_node *current, int type)
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

static char	*hrdoc_create_word(t_node *current, int type)
{
	size_t	i;
	size_t	size;
	char	*word;
	t_node	*iterator;

	size = hrdoc_get_word_size(current, type);
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

static t_node	*hrdoc_init_word(t_node *src, t_node *curr, int mode)
{
	char	*word;

	word = hrdoc_create_word(src, src->type);
	if (!word)
		return (NULL);
	if (mode == FIRST)
		return (t_node_create(0, word, src->type));
	else if (mode == NEXT)
		return (t_node_addlast(curr, 0, word, src->type));
	return (NULL);
}

static void	hrdoc_skip_chars(t_node **src, t_node **head)
{
	size_t	to_skip;

	to_skip = ft_strlen((*head)->word);
	if (to_skip > 1)
	{
		while (--to_skip)
			if (*src)
				*src = (*src)->next;
	}
}

void	hrdoc_get_lst_tokens(t_node *chars, t_node **tokens)
{
	t_node	*curr;

	if (!chars)
		return ;
	*tokens = hrdoc_init_word(chars, NULL, FIRST);
	hrdoc_skip_chars(&chars, tokens);
	chars = chars->next;
	curr = *tokens;
	while (chars)
	{
		curr->next = hrdoc_init_word(chars, curr, NEXT);
		if (ft_lstsize_2(*tokens) == 1)
			return ;
		hrdoc_skip_chars(&chars, &curr->next);
		if (chars)
			chars = chars->next;
		if (curr)
			curr = curr->next;
	}
}
