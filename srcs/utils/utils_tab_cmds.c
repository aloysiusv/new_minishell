/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:58:51 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 21:43:26 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tab_files(t_file *files, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (files[i].name)
			free(files[i].name);
		i++;
	}
	free(files);
}

static void	delete_cmd(t_cmd cmd)
{
	if (cmd.tokens)
		t_node_delete_lst(&cmd.tokens);
	if (cmd.command)
		free_tab(cmd.command);
	if (cmd.files)
		free_tab_files(cmd.files, cmd.nb_files);
}

void	delete_cmds_tab(t_cmd **cmds)
{
	size_t	i;
	size_t	nb;

	if (!*cmds)
		return ;
	nb = (*cmds)->nb_cmds;
	i = 0;
	while (i < nb)
	{
		delete_cmd((*cmds)[i]);
		i++;
	}
	free(*cmds);
	*cmds = NULL;
}
