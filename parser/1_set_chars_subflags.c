/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_set_chars_subflags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:36:15 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/01 14:19:53 by lrandria         ###   ########.fr       */
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
		{
			if (iterator->type == DOLLAR && iterator->in_dquotes)
				iterator->type = DOLLAR;
			else
				iterator->type = LITERAL;
		}
		iterator = iterator->next;
	}
}

static void	set_quote_flags(t_node **iterator, char quote)
{
	if (!(*iterator)->next)
		return ;
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
		*iterator = (*iterator)->next;
}

static int	check_closing_quotes(t_node *head)
{
	t_node  *iterator;

	if (!head)
		return (-1);
	iterator = head;
	while (iterator->next)
		iterator = iterator->next;
	if (iterator->in_squotes || iterator->in_dquotes)
		return (-1);
	return (0);
}

void	set_chars_subflags(t_node **head)
{
	t_node	*iterator;

	if (!*head)
		return ;
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
	if (check_closing_quotes(*head) == -1)
	{
		print_error("unclosed quotes\n", 2);
		return ;
	}
	set_literals(head);
	set_expansion_flags(head);
}
