/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_get_lst_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:31:45 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/29 22:54:19 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void		fill_cmds_fields(t_cmd **cmds)
// {
// 	size_t	i;
// 	t_node	*iterator;

// 	i = 0;
// 	iterator = (*cmds)->tokens;
// 	while (cmds[i])
// 	{
// 		cmds[i]->index = i;
// 		get_command(cmds[i]);
// 		get_outfiles(cmds[i]);
// 		i++;
// 	}
// }

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

static  size_t  get_nb_cmds(t_node *tokens)
{
    t_node  *iterator;
    size_t  nb_cmds;

    iterator = tokens;
	nb_cmds = 1;
    while (iterator)
    {
        if (iterator->type == PIPE)
			nb_cmds++;
        iterator = iterator->next;
    }
	return (nb_cmds);
}

void	get_lst_cmds(t_cmd **cmds, t_node **tokens, t_shell *sh)
{
	t_node	*iterator;
	size_t	i;

    sh->nb_cmds = get_nb_cmds(*tokens);
	*cmds = ft_calloc(sh->nb_cmds, sizeof(t_cmd) + 1);
	if (!*cmds)
		return ;
	i = 0;
	iterator = *tokens;
	while (i < sh->nb_cmds)
	{
		while (iterator && iterator->type != PIPE)
		{
			push_back(&(*cmds)[i].tokens, create_node(0, ft_strdup(iterator->word), iterator->type));
			iterator = iterator->next;
		}
		if (iterator && iterator->type == PIPE)
			iterator = iterator->next;
		i++;
	}
	// fill_cmds_fields(cmds);
}
