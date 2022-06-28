/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_set_expansion_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:28:49 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/28 20:22:19 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_it_weird(t_node **iterator)
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
	else if ((*iterator)->next && ft_isset((*iterator)->next->charac, "?_"))
	{
		(*iterator)->next->type = DOLLAR_SPECIAL;
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
			if (is_it_weird(&iterator) == 1)
			{
				iterator = iterator->next;
				continue ;
			}
			else 
			{
				iterator = iterator->next;
				while (iterator && iterator->type == LITERAL)
				{
				iterator->type = DOLLAR_TRAIL;
				iterator = iterator->next;
				}
			}
		}
		if (iterator)
			iterator = iterator->next;
	}
}
