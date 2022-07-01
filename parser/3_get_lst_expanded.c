/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get_lst_expanded.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:18:30 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/01 03:42:41 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*find_matching_var(t_node **tokens, t_node *current, t_env *vars)
// {
// 	size_t	i;
// 	size_t	len;
// 	t_node	*new;
// 	t_env	*env_var;
// 	char	**expanded;

// 	expanded = NULL;
// 	env_var = vars;
// 	while (env_var)
// 	{
// 		if (ft_strncmp(current->word, env_var->key,
// 			ft_strlen(current->word) + 1) == 0)
// 		{
// 			expanded = ft_split(env_var->value, ' ');
// 			break ;
// 		}
// 		env_var = env_var->next;
// 	}
// 	len = get_tab_size(expanded);
// 	if (len > 1)
// 	{
// 		i = 0;
// 		while (i < len - 1)
// 		{
// 			new = create_node(0, expanded[i], LITERAL);
// 			insert_tokens(tokens, current, &new);
// 			i++;
// 		}
// 		return (expanded[i + 1]);
// 	}
// 	else if (len == 1)
// 		return (expanded[0]);
// 	return (NULL);
// }

// void	expand_word(t_node **iterator, t_env *vars)
// {
// 	char	*to_print;

// 	if (!*iterator || !(*iterator)->next)
// 		return ;
// 	to_print = NULL;
// 	*iterator = (*iterator)->next;
// 	if (ft_strncmp((*iterator)->word, "?", 2) == 0)
// 	{
// 		free((*iterator)->word);
// 		(*iterator)->word = ft_itoa(g_exit_code);
// 		(*iterator)->type = LITERAL;
// 		return ;
// 	}
// 	to_print = find_matching_var(iterator, *iterator, vars);
// 	if (to_print)
// 	{
// 		// if (check_to_print(to_print, iterator) == 1)
// 		// 	return ;
// 		free((*iterator)->word);
// 		(*iterator)->word = ft_strdup(to_print);
// 		(*iterator)->type = LITERAL;
// 		free(to_print);
// 	}
// 	else
// 		(*iterator)->type = USELESS;
// }

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

static void	set_useless_quotes(t_node **head)
{
	t_node	*iterator;

	iterator = *head;
	while (iterator)
	{
		if (iterator->type == SQUOTE || iterator->type == DQUOTE)			// || (iterator->type == BLANK && !iterator->in_dquotes
			iterator->type = USELESS;
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
			expand_word(&iterator, vars);
		iterator = iterator->next;
	}
	delete_useless_tokens(tokens, DOLLAR);
	set_useless_quotes(tokens);
	delete_useless_tokens(tokens, USELESS);
}
