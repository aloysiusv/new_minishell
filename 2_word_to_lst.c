/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_word_to_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:56:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 04:16:21 by lrandria         ###   ########.fr       */
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

static t_node	*init_word(t_node *src, t_node *curr, int mode)
{
	char	*word;

	word = create_word(src, src->type);
	if (!word)
		return (NULL);
	if (ft_strncmp(word, "<<", 3) == 0)
		src->type = HRDOC;
	else if (ft_strncmp(word, ">>", 3) == 0)
		src->type = APPEND;
	if (mode == FIRST_WORD)
		return (create_node(0, word, src->type));
	else if (mode == NEXT_WORD)
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

t_node			*stock_words_to_lst(t_node *src, t_node **head)
{
	t_node	*curr;

	if (!src)
		return (NULL);
	*head = init_word(src, NULL, FIRST_WORD);
	set_qflags_and_skip_chars(&src, head);
	src = src->next;
	curr = *head;
	while (src)
	{
		curr->next = init_word(src, curr, NEXT_WORD);
		set_qflags_and_skip_chars(&src, &curr->next);
		src = src->next;
		curr = curr->next;
	}
	return (*head);
}

void		words_to_lst(t_node *src, t_node **dest)
{
	t_node	*iterator;

	*dest = stock_words_to_lst(src, dest);
	iterator = *dest;
	while (iterator)
	{
		printf("[%s] => in_squotes [%d] || in_dquotes [%d] || type [%d]\n",
			iterator->word, iterator->in_squotes,
				iterator->in_dquotes, iterator->type);
		iterator = iterator->next;
	}
}

// int main(void)
// {
// 	char	*cmdline = "  \"COOOL\" CO |'||'| \\ ? <<<' > ";
// 	t_node	*src;
// 	t_node	*dest;

// 	src = NULL;
// 	dest = NULL;
// 	characters_to_lst(cmdline, &src);
// 	printf("==================================================================\n");
// 	words_to_lst(src, &dest);
// 	delete_lst(&src);
// 	delete_lst(&dest);
// 	return (0);
// }
