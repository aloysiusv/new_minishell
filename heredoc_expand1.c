/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:10:19 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 16:49:27 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hrdoc_set_expansion_flags(t_node **head)
{
	t_node	*iterator;

	iterator = *head;
	while (iterator)
	{
		if (iterator->type == DOLLAR && iterator->next
			&& iterator->next->type == LITERAL)
		{
			iterator = iterator->next;
			while (iterator && iterator->type == LITERAL)
			{
				iterator->type = DOLLAR_TRAIL;
				if (iterator)
					iterator = iterator->next;
			}
		}
		else
			iterator->type = LITERAL;
		if (iterator)
			iterator = iterator->next;
	}
}

static void	hrdoc_get_next_char(char *str, size_t *i, t_node **curr)
{
	if (str[*i] == '$')
		(*curr)->next = add_bottom_node(*curr, '$', NULL, DOLLAR);
	else if (ft_isset(str[*i], ALL_SPACES) == 1)
		(*curr)->next = add_bottom_node(*curr, ' ', NULL, BLANK);
	else
		(*curr)->next = add_bottom_node(*curr, str[*i], NULL, LITERAL);
}

static t_node	*hrdoc_get_first_char(char *str)
{
	if (str[0] == '$')
		return(create_node('$', NULL, DOLLAR));
	else if (ft_isset(str[0], ALL_SPACES) == 1)
		return(create_node(' ', NULL, BLANK));
	else
		return(create_node(str[0], NULL, LITERAL));
}

int	hrdoc_get_lst_chars(char *line, t_node **chars)
{
	size_t	i;
	t_node	*curr;

	if (!line || !*line)
		return (-1);
	*chars = hrdoc_get_first_char(line);
	curr = *chars;
	i = 1;
	while (line[i])
	{
		hrdoc_get_next_char(line, &i, &curr);
		if (!curr)
			return (-1);
		curr = curr->next;
		i++;
	}
	hrdoc_set_expansion_flags(chars);
	return (0);
}
