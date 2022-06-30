/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get_lst_expanded.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:18:30 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/30 02:26:18 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_input_filetype(t_node **tokens)
{
    t_node	*iterator;

	iterator = *tokens;
	while (iterator && iterator->next)
	{
		if (iterator->type == RD_INPUT)
		{
			iterator = iterator->next;
			while (iterator && iterator->type == BLANK)
				iterator = iterator->next;
            iterator->type = INFILE;
		}
	    else if (iterator->type == HRDOC && iterator->next)
		{
			iterator = iterator->next;
			while (iterator && iterator->type == BLANK)
				iterator = iterator->next;
            iterator->type = LIMITER;
		}
        iterator = iterator->next;
    }
}

static void	set_output_filetype(t_node **tokens)
{
    t_node	*iterator;

	iterator = *tokens;
	while (iterator && iterator->next)
	{
        if (iterator->type == RD_OUTPUT && iterator->next)
		{
			iterator = iterator->next;
			while (iterator->type == BLANK)
				iterator = iterator->next;
			iterator->type = OUTFILE;
		}
		else if (iterator->type == APPEND && iterator->next)
		{
			iterator = iterator->next;
			while (iterator->type == BLANK)
				iterator = iterator->next;
			iterator->type = OUTFILE_A;
		}
		iterator = iterator->next;
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
	delete_useless_tokens(tokens, USELESS);
	set_input_filetype(tokens);
    set_output_filetype(tokens);
}
