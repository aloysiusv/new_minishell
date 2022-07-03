/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_set_expansion_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:28:49 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 20:15:06 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_dollar_trail_flags(t_node **iterator)
{
	while (*iterator && (*iterator)->type == LITERAL)
	{
		if (ft_isset((*iterator)->charac, " 	\'\"|<>"))
			return ;
		(*iterator)->type = DOLLAR_TRAIL;
		if (*iterator)
			*iterator = (*iterator)->next;
	}
}

static int	special_expansions(t_node **iterator)
{
	if (!(*iterator)->next || ((*iterator)->next
		&& ft_isset((*iterator)->next->charac, ALL_SPACES)))
	{
		(*iterator)->type = LITERAL;
		return (1);
	}
	else if ((*iterator)->next && (*iterator)->next->type == DOLLAR)
	{
		(*iterator)->type = LITERAL;
		(*iterator)->next->type = LITERAL;
		return (1);
	}
	else if ((*iterator)->next && ft_isdigit((*iterator)->next->charac))
	{
		(*iterator)->type = USELESS;
		(*iterator)->next->type = USELESS;
		return (1);
	}
	else if ((*iterator)->next && ft_isset((*iterator)->next->charac, "?"))
	{
		(*iterator)->next->type = DOLLAR_TRAIL;
		return (1);
	}
	return (0);
}

void	set_expansion_flags(t_node **head)
{
	t_node	*iterator;

	iterator = *head;
	while (iterator)
	{
		if (iterator->type == DOLLAR)
		{
			if (special_expansions(&iterator) == 1)
			{
				if (iterator)
					iterator = iterator->next;
				continue ;
			}
			if (iterator)
				iterator = iterator->next;
			set_dollar_trail_flags(&iterator);
		}
		else
			if (iterator)
				iterator = iterator->next;
	}
}
