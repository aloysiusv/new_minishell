/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_get_lst_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:43:34 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 16:07:46 by lrandria         ###   ########.fr       */
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

static char		*create_word(t_node *current, int type)
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

t_node	*init_word(t_node *src, t_node *curr, int mode)
{
	char	*word;

	word = create_word(src, src->type);
	if (!word)
		return (NULL);
	if (ft_strncmp(word, "<<", 3) == 0)
		src->type = HRDOC;
	else if (ft_strncmp(word, ">>", 3) == 0)
		src->type = APPEND;
	if (mode == FIRST)
		return (create_node(0, word, src->type));
	else if (mode == NEXT)
		return(add_bottom_node(curr, 0, word, src->type));
	return (NULL);
}

static void		set_qflags_and_skip_chars(t_node **src, t_node **head)
{
	size_t	to_skip;

	if ((*src)->in_dquotes == true)
		(*head)->in_dquotes = true;
	else if ((*src)->in_squotes == true)
		(*head)->in_squotes = true;
	to_skip = ft_strlen((*head)->word);
	if (to_skip > 1 )
	{
		while (--to_skip)
			if (*src)
				*src = (*src)->next;
	}
}

void	get_lst_tokens(t_node *chars, t_node **tokens)
{
	t_node	*curr;

	if (!chars)
		return ;
	*tokens = init_word(chars, NULL, FIRST);
	set_qflags_and_skip_chars(&chars, tokens);
	chars = chars->next;
	curr = *tokens;
	while (chars)
	{
		curr->next = init_word(chars, curr, NEXT);
		if (ft_lstsize_2(*tokens) == 1)
			return ;
		set_qflags_and_skip_chars(&chars, &curr->next);
		if (chars)
			chars = chars->next;
		if (curr)
			curr = curr->next;
	}
}
