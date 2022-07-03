/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_set_chars_subflags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:36:15 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 16:43:47 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_literals(t_node **head)
{
	t_node	*iterator;

	iterator = *head;
	while (iterator)
	{
		if ((iterator->in_squotes || iterator->in_dquotes)
			&& (iterator->type != SQUOTE && iterator->type != DQUOTE))
		{
			if (iterator->type == DOLLAR && iterator->in_dquotes)
				iterator->type = DOLLAR;
			else
				iterator->type = LITERAL;
		}
		if (iterator)
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

static int	check_closing_quotes2(t_node **head, int type)
{
	*head = (*head)->next;
	while (*head && (*head)->type != type)
		*head = (*head)->next;
	if (!*head || (*head)->type != type)
		return (-1);
	return (0);
}

static int	check_closing_quotes(t_node *head)
{
	t_node  *iterator;

	iterator = head;
	if (ft_lstsize_2(head) == 1 && 
		(iterator->type == SQUOTE || iterator->type == DQUOTE))
		return (-1);
	while (iterator)
	{
		if (iterator->type == SQUOTE || iterator->type == DQUOTE)
		{
			if (check_closing_quotes2(&iterator, iterator->type) == -1)
				return (-1);
		}
		iterator = iterator->next;
	}
	return (0);
}

int	set_chars_subflags(t_node **head)
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
	if (check_closing_quotes(*head) == -1)
	{
		print_error("unclosed quotes\n", 2);
		return (-1);
	}
	set_literals(head);
	set_expansion_flags(head);
	return (0);
}
