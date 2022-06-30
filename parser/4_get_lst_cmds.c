/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_get_lst_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:31:45 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/30 02:44:19 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_files_tab(t_file *files, size_t nb_files)
{
	size_t	i;

	i = 0;
	while (i < nb_files)
	{
		// if (files[i].name)
		printf("file[%zu] => [%s][%d]\n", i, files[i].name, files[i].type);
		i++;
	}
}

static void	print_cmds_tab(t_cmd *cmds)
{
	size_t	i;

	if (!cmds)
		return ;
	i = 0;
	while (i < cmds->nb_cmds)
	{
		printf("CMD[%zu] =>\n", i);
		print_files_tab(cmds[i].files, cmds[i].nb_files);
		i++;
	}
}

// static void	print_list(t_node *tokens, size_t index)
// {
// 	t_node	*iterator;

// 	if (!tokens)
// 		return ;
// 	iterator = tokens;
// 	while (iterator)
// 	{
// 		printf("list[%zu] => word [%s] type [%d]\n",
// 			index, iterator->word, iterator->type);
// 		iterator = iterator->next;
// 	}
// }

static size_t	how_many_redirs(t_node *tokens)
{
	size_t	redirs;

	redirs = get_nb_types(tokens, INFILE);
	redirs += get_nb_types(tokens, LIMITER);
	redirs += get_nb_types(tokens, OUTFILE);
	redirs += get_nb_types(tokens, OUTFILE_A);
	return (redirs);

}

static void	fill_cmds_fields(t_cmd *cmd)  // CAT < MAKEFILE
{
	size_t	i;
	t_node	*iterator;

	cmd->nb_files = how_many_redirs(cmd->tokens);
	printf("nb_files = [%zu]\n", cmd->nb_files);
	cmd->files = ft_calloc(cmd->nb_files, sizeof(t_file));
	if (!cmd)
		return ;
	i = 0;
	iterator = cmd->tokens;
	while (iterator)
	{
		if (iterator->type == INFILE || iterator->type == LIMITER
			|| iterator->type == OUTFILE || iterator->type == OUTFILE_A)
		{
			cmd->files[i].name = ft_strdup(iterator->word);
			cmd->files[i].type = iterator->type;
			i++;
		}
		iterator = iterator->next;
	}
}

static void	push_back(t_node **alst, t_node *new)
{
	t_node	*new_alst;

	if (alst == 0 || new == 0)
		return ;
	if (*alst == 0)
	{
		*alst = new;
		return ;
	}
	new_alst = *alst;
	while (new_alst->next != NULL)
		new_alst = new_alst->next;
	new_alst->next = new;
}

void	get_lst_cmds(t_cmd **cmds, t_node **tokens)
{
	t_node	*iterator;
	size_t	nb_cmds;
	size_t	i;

    nb_cmds = get_nb_types(*tokens, PIPE) + 1;
	*cmds = ft_calloc(nb_cmds, sizeof(t_cmd) + 1);
	if (!*cmds)
		return ;
	i = 0;
	iterator = *tokens;
	while (i < nb_cmds)
	{
		(*cmds)[i].index = i;
		(*cmds)[i].nb_cmds = nb_cmds;
		while (iterator && iterator->type != PIPE)
		{
			push_back(&(*cmds)[i].tokens,
				create_node(0, ft_strdup(iterator->word), iterator->type));
			iterator = iterator->next;
		}
		fill_cmds_fields(&(*cmds)[i]);
		// print_list((*cmds)[i].tokens, i);
		if (iterator && iterator->type == PIPE)
			iterator = iterator->next;
		i++;
	}
	print_cmds_tab(*cmds);
}
