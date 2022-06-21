/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_word_to_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:56:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/21 04:13:23 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_literals(t_node **head)
{
	t_node	*iterator;

	iterator = *head;
	while (iterator)
	{
		if (iterator->in_squotes || iterator->in_dquotes)
			iterator->type = LITERAL;
		if (iterator)
			iterator = iterator->next;
	}
}

static void	set_quote_flags(t_node **iterator, char quote)
{
	*iterator = (*iterator)->next;
	while (*iterator && (*iterator)->charac != quote)
	{
		if (quote == '\'')
			(*iterator)->in_squotes = true;
		else if (quote == '\"')
			(*iterator)->in_dquotes = true;
		*iterator = (*iterator)->next;
	}
	if (*iterator)
		(*iterator) = (*iterator)->next;
}

void	set_subflags(t_node **head)
{
	t_node	*iterator;

	iterator = *head;
	while (iterator)
	{
		if (iterator->charac == '\'')
			set_quote_flags(&iterator, '\'');
		else if (iterator->charac == '\"')
			set_quote_flags(&iterator, '\"');
		if (iterator)
			iterator = iterator->next;
	}
	set_literals(head);
}

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

static char	*create_word(t_node *current, int type)
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
	printf("size = [%zu]\n", size);
	while (i < size)
	{
		word[i] = iterator->charac;
		if (iterator)
			iterator = iterator->next;
		i++;
	}
	word[i] = '\0';
	printf("word created is [%s]\n", word);
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

static void	set_qflags_and_skip_chars(t_node **src, t_node **head)
{
	size_t	to_skip;

	if ((*src)->in_dquotes == true)
		(*head)->in_dquotes = true;
	else if ((*src)->in_squotes == true)
		(*head)->in_squotes = true;
	to_skip = ft_strlen((*head)->word);
	if (to_skip > 1 )
	{
		while (to_skip--)
		{
			if (*src)
				*src = (*src)->next;
			// to_skip--;
		}
	}
}

t_node *stock_words_to_lst(t_node *src, t_node **head)
{
	t_node	*curr;

	if (!src)
		return (NULL);
	*head = init_word(src, NULL, FIRST_WORD);
	set_qflags_and_skip_chars(&src, head);
	curr = *head;
	printf("src->char = [%c]\n", src->charac);
	while (src)
	{
		curr->next = init_word(src, curr, NEXT_WORD);
		set_qflags_and_skip_chars(&src, &curr->next);
		// else
		src = src->next;
		curr = curr->next;
	}
	return (*head);
}

static void	characters_to_lst(char *cmdline, t_node **src, t_node **iterator)
{
    *src = cmdline_to_lst(cmdline, src);
	set_subflags(src);
    *iterator = *src;
	while (*iterator)
    {
        printf("[%c] => in_squotes [%d] || in_dquotes [%d]\n", (*iterator)->charac, (*iterator)->in_squotes, (*iterator)->in_dquotes);
		*iterator = (*iterator)->next;
    }
}

static void	words_to_lst(t_node *src, t_node **dest, t_node **iterator)
{
	*dest = stock_words_to_lst(src, dest);
    *iterator = *dest;
	while (*iterator)
    {
        printf("[%s] => in_squotes [%d] || in_dquotes [%d]\n", (*iterator)->word, (*iterator)->in_squotes, (*iterator)->in_dquotes);
		*iterator = (*iterator)->next;
    }
	while ((*dest)) 
	{
		printf("freeing [%s]\n", (*dest)->word);
		free((*dest)->word);
		*dest = (*dest)->next;
	}
}

int main(void)
{
	char	*cmdline = "  COOOL CO |||| \\ ? <<<' > ";
	t_node  *iterator;
	t_node	*src;
	t_node	*dest;

	src = (t_node *)malloc(sizeof(t_node));
	if (!src)
		return (-1);
	dest = (t_node *)malloc(sizeof(t_node));
	if (!dest)
		return (free(src), -1);
	characters_to_lst(cmdline, &src, &iterator);
	printf("==================================================================\n");
	words_to_lst(src, &dest, &iterator);
	delete_lst(&src);
	delete_lst(&dest);
	free(src);
	free(dest);
	return (0);
}
