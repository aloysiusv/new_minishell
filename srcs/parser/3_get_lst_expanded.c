/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get_lst_expanded.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:18:30 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 20:47:34 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	not_expand(t_node **iterator)
{
	if ((*iterator)->next && (*iterator)->next->type == DOLLAR_TRAIL)
	{
		free((*iterator)->word);
		(*iterator)->word = ft_strjoin("$", (*iterator)->next->word);
		(*iterator)->type = LITERAL;
		(*iterator)->next->type = USELESS;
	}
	if (*iterator)
		*iterator = (*iterator)->next;
}

static void	set_useless_quotes(t_node **head) /* new */
{
	t_node	*iterator;

	iterator = *head;
	while (iterator)
	{
		if (iterator->type == SQUOTE || iterator->type == DQUOTE
			|| iterator->type == DOLLAR)
			iterator->type = USELESS;
		if (iterator)
			iterator = iterator->next;
	}
}

void	get_lst_expanded(t_node **tokens, t_env *vars)
{
	t_node	*iterator;

	if (!tokens)
		return ;
	iterator = *tokens;
	while (iterator)
	{
		if (iterator->type == HRDOC)
		{
			if (iterator->next)
				iterator = iterator->next;
			while (iterator && (iterator->type == BLANK
				|| iterator->type == SQUOTE || iterator->type == DQUOTE))
				iterator = iterator->next;
			if (iterator->type == DOLLAR
				|| (iterator->type == DOLLAR && (iterator->in_squotes
				|| iterator->in_dquotes)))
					not_expand(&iterator);
		}
		else if (iterator->type == DOLLAR)
			expand_word(&iterator, vars);
		if (iterator)
			iterator = iterator->next;
	}
	set_useless_quotes(tokens); /* new */
	t_node_delete_useless_tokens(tokens, USELESS);
}
