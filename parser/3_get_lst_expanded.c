/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get_lst_expanded.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:18:30 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/29 12:38:44 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void		expand_word(t_node **iterator, t_env *vars)
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
		return ;
	}
	to_print = find_matching_var(*iterator, vars);
	if (to_print)
	{
		free((*iterator)->word);
		(*iterator)->word = ft_strdup(to_print);
		(*iterator)->type = LITERAL;
		printf("word[%s] type[%d]\n", (*iterator)->word, (*iterator)->type);
		free(to_print);
	}
	else
	{
		(*iterator)->type = USELESS;
		printf("useless word[%s] type[%d]\n", (*iterator)->word, (*iterator)->type);
	}
}

void		get_lst_expanded(t_node **tokens, t_env *vars)
{
	t_node	*iterator;

	if (!tokens)
		return ;
	iterator = *tokens;
	while (iterator)
	{
		if (iterator->type == DOLLAR)
		{
			expand_word(&iterator, vars);
			delete_useless_tokens(tokens, USELESS);
		}
		iterator = iterator->next;
	}
}
