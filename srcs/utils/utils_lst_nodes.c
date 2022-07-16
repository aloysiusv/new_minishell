/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmachrou <wmachrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:39:17 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 15:23:02 by wmachrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*t_node_create(char my_char, char *my_word, int my_type)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->charac = '\0';
	new->word = NULL;
	if (my_char)
		new->charac = my_char;
	if (my_word)
		new->word = my_word;
	new->type = my_type;
	new->in_squotes = false;
	new->in_dquotes = false;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_node	*t_node_addlast(t_node *current_last, char value, char *word, int type)
{
	t_node	*bottom;

	bottom = t_node_create(value, word, type);
	if (!bottom)
		return (NULL);
	if (current_last)
	{
		current_last->next = bottom;
		bottom->prev = current_last;
		bottom->next = NULL;
	}
	return (bottom);
}

void	skip_blanks(t_node **iterator)
{
	while (*iterator && (*iterator)->type == BLANK)
		*iterator = (*iterator)->next;
}

void	t_node_push_new(t_node **tokens, t_node *new)
{
	t_node	*new_token;

	if (!tokens || !new)
		return ;
	if (*tokens == NULL)
	{
		*tokens = new;
		return ;
	}
	new_token = *tokens;
	while (new_token->next)
		new_token = new_token->next;
	new_token->next = new;
}

void	delete_all(t_shell *sh)
{
	t_node_delete_lst(&sh->chars);
	t_node_delete_lst(&sh->tokens);
	delete_cmds_tab(sh);
}
