/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:09:08 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 21:18:59 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hrdoc_get_lst_expanded(t_node **tokens, t_env *vars)
{
	t_node	*iterator;

	if (!tokens)
		return ;
	iterator = *tokens;
	while (iterator)
	{
		if (iterator->type == DOLLAR)
			expand_word(&iterator, vars);
		if (iterator)
			iterator = iterator->next;
	}
	t_node_delete_useless_tokens(tokens, USELESS);
}
