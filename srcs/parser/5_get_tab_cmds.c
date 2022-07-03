/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_get_tab_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:39:48 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 21:40:04 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_and_join(char **copy, t_node **iterator)
{
	*copy = ft_strdup((*iterator)->next->word);
	free((*iterator)->next->word);
	(*iterator)->next->word = ft_strjoin((*iterator)->word, *copy);
	(*iterator)->type = USELESS;
	free((*iterator)->word);
	free(*copy);
	(*iterator)->word = NULL;
}

static void	join_literals(t_node **tokens)
{
	t_node	*iterator;
	char	*copy;

	if (!*tokens)
		return ;
	iterator = *tokens;
	while (iterator)
	{
		if (iterator->type == LITERAL
			&& iterator->next && iterator->next->type == LITERAL)
			copy_and_join(&copy, &iterator);
		else if (iterator->type == BLANK)
			iterator->type = USELESS;
		if (iterator)
			iterator = iterator->next;	
	}
}

static void	fill_cmd_tab(t_cmd **cmds, size_t *i) /* if segfault, check here */
{
	join_literals(&(*cmds)[*i].tokens);
	t_node_delete_useless_tokens(&(*cmds)[*i].tokens, USELESS);
	set_filetype(&(*cmds)[*i].tokens, RD_INPUT, BLANK, INFILE);
	set_filetype(&(*cmds)[*i].tokens, RD_OUTPUT, BLANK, OUTFILE);
	set_filetype(&(*cmds)[*i].tokens, HRDOC, BLANK, LIMITER);
	set_filetype(&(*cmds)[*i].tokens, APPEND, BLANK, OUTFILE_A);
	get_io_files(&(*cmds)[*i]);
	set_filename_flags(&(*cmds)[*i].tokens);
	t_node_delete_useless_tokens(&(*cmds)[*i].tokens, FILENAME);
	(*cmds)[*i].command = lst_to_tab((*cmds)[*i].tokens);
}

static void	split_cmd_tokens(t_node **new, t_node **t, t_cmd **cmd, size_t *i)
{
	*new = t_node_create(0, ft_strdup((*t)->word), (*t)->type);
	t_node_push_new(&(*cmd)[*i].tokens, *new); /* if segfault, check here */
	if ((*t)->in_squotes)
		(*new)->in_squotes = true;
	else if ((*t)->in_dquotes)
		(*new)->in_dquotes = true;
	if (*t)
		*t = (*t)->next;
}

size_t	get_tab_cmds(t_cmd **cmds, t_node **tokens)
{
	t_node	*iterator;
	t_node	*new;
	size_t	nb_cmds;
	size_t	i;

	nb_cmds = get_nb_types(*tokens, PIPE) + 1;
	*cmds = ft_calloc(nb_cmds, sizeof(t_cmd) + 1);
	if (!*cmds)
		return (0);
	i = 0;
	iterator = *tokens;
	while (i < nb_cmds)
	{
		(*cmds)[i].index = i;
		(*cmds)[i].nb_cmds = nb_cmds;
		(*cmds)[i].index_files = 0;
		while (iterator && iterator->type != PIPE)
			split_cmd_tokens(&new, &iterator, cmds, &i);
		fill_cmd_tab(cmds, &i);
		if (iterator && iterator->type == PIPE)
			iterator = iterator->next;
		i++;
	}
	return (nb_cmds);
}
