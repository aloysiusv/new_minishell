/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:01:37 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 21:11:11 by lrandria         ###   ########.fr       */
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
		if (ft_strcmp(current->word, env_var->key) == 0)
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
	if (ft_strcmp((*iterator)->word, "?") == 0)
	{
		free((*iterator)->word);
		(*iterator)->word = ft_itoa(g_exit);
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
