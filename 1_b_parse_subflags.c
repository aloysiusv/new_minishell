/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_b_parse_subflags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:56:52 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/21 21:19:53 by lrandria         ###   ########.fr       */
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

static void	set_subflags(t_node **head)
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

void	get_lst_chars(char *cmdline, t_node **src)
{
    t_node  *iterator;

    *src = create_lst_chars(cmdline, src);
	set_subflags(src);
    iterator = *src;
	while (iterator)
    {
        printf("[%c] => in_squotes [%d] || in_dquotes [%d]\n", 
            iterator->charac, iterator->in_squotes, iterator->in_dquotes);
		iterator = iterator->next;
    }
}