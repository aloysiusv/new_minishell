/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get_lst_expanded.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:18:30 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/29 00:13:46 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_expansions(t_node *tokens)
{
	t_node *iterator;

	if (!tokens)
		return (0);
	iterator = tokens;
	while (iterator)
	{
		if (iterator->type == DOLLAR)
			return (1);
		iterator = iterator->next;
	}
	return (0);
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

void		make_expands(t_node **tokens, t_env *vars)
{
	t_node	*iterator;
	char	*to_print;

	iterator = *tokens;
	if (!iterator || !iterator->next)
		return ;
	while (iterator)
	{
		if (iterator->type == DOLLAR && iterator->next)
		{
			iterator->type = USELESS;
			iterator = iterator->next;
			to_print = find_matching_var(iterator, vars);
			if (to_print)
			{
				free(iterator->word);
				iterator->word = ft_strdup(to_print);
				iterator->type = LITERAL;
				printf("word[%s] type[%d]\n", iterator->word, iterator->type);
				free(to_print);
			}
			else
			{
				iterator->type = USELESS;
				printf("useless word[%s] type[%d]\n", iterator->word, iterator->type);
			}
		}
		iterator = iterator->next;
	}
}

t_node		*init_real_word(t_node **tokens, t_node *curr, int mode)
{
	char	*word;

	if (!*tokens)
		return (NULL);
	word = ft_strdup((*tokens)->word);
	printf("init real word: [%s]\n", word);
	if (!word)
		return (NULL);
	if (mode == FIRST)
		return (create_node(0, word, (*tokens)->type));
	else if (mode == NEXT)
		return(add_bottom_node(curr, 0, word, (*tokens)->type));
	return (NULL);
}

void		get_lst_expanded(t_node **expanded, t_node **tokens, t_env *vars)
{
	t_node	*curr;

	if (!tokens)
		return ;
	if (has_expansions(*tokens) == 1)
	{
		make_expands(tokens, vars);
		delete_useless_tokens(tokens);
		*expanded = init_real_word(tokens, NULL, FIRST);
		*tokens = (*tokens)->next;
		curr = *expanded;
		while (*tokens)
		{
			curr->next = init_real_word(tokens, curr, NEXT);
			if (ft_lstsize_2(*expanded) == 1)
				return ;
			*tokens = (*tokens)->next;
			curr = curr->next;
		}
	}
}
