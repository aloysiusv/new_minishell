/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_set_chars_subflags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:36:15 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/29 04:22:49 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_useless_quotes(t_node **head)
{
	t_node	*iterator;

	iterator = *head;
	while (iterator)
	{
		if (iterator->type == SQUOTE || iterator->type == DQUOTE)
			iterator->type = USELESS;
		iterator = iterator->next;
	}
}

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
			else if (iterator->type == BLANK)
				iterator->type = BLANK;
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
	set_literals(head);
	set_expansion_flags(head);
	set_useless_quotes(head);
}
