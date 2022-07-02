/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get_lst_expanded.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:18:30 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 16:07:18 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	not_expand(t_node **iterator)  /* new */
{
	if ((*iterator)->next && (*iterator)->next->type == DOLLAR_TRAIL)
	{
		free((*iterator)->word);
		(*iterator)->word = ft_strjoin((*iterator)->word, (*iterator)->next->word);
		(*iterator)->type = LIMITER;
		(*iterator)->next->type = USELESS;
	}
}

static char	*find_matching_var(t_node *current, t_env *vars)
{
	t_env	*env_var;
	char	*expanded;

	expanded = NULL;
	env_var = vars;
	while (env_var)
	{
		if (ft_strncmp(current->word, env_var->key,
			ft_strlen(current->word) + 1) == 0)
		{
			expanded = ft_strdup(env_var->value);
			break ;
		}
		env_var = env_var->next;
	}
	return (expanded);
}

void	expand_word(t_node **iterator, t_env *vars)
{
	char	*to_print;

	if (!*iterator || !(*iterator)->next)
		return ;
	to_print = NULL;
	(*iterator)->type = USELESS;
	*iterator = (*iterator)->next;
	if (ft_strncmp((*iterator)->word, "?", 2) == 0)
	{
		free((*iterator)->word);
		(*iterator)->word = ft_itoa(g_exit_code);
		(*iterator)->type = LITERAL;
		return ;
	}
	to_print = find_matching_var(*iterator, vars);
	if (to_print)
	{
		free((*iterator)->word);
		(*iterator)->word = ft_strdup(to_print);
		(*iterator)->type = LITERAL;
		free(to_print);
	}
	else
		(*iterator)->type = USELESS;
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
		if (iterator->type == DOLLAR)
		{
			if (iterator->prev && iterator->prev->type == HRDOC)
				not_expand(&iterator);
			else
				expand_word(&iterator, vars);
		}
		if (iterator)
			iterator = iterator->next;
	}
	set_useless_quotes(tokens); /* new */
	delete_useless_tokens(tokens, USELESS);
}
