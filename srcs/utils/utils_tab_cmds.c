/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:58:51 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 23:06:42 by lrandria         ###   ########.fr       */
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

void	delete_cmd(t_cmd cmd)
{
	if (cmd.tokens)
		t_node_delete_lst(&cmd.tokens);
	if (cmd.command)
		free_tab(cmd.command);
	if (cmd.files)
		free_tab_files(cmd.files, cmd.nb_files);
}

void	delete_cmds_tab(t_shell *sh)
{
	size_t	i;

	i = 0;
	while (i < sh->nb_cmds)
	{
		delete_cmd(sh->cmds[i]);
		i++;
	}
	free(sh->cmds);
	sh->cmds = NULL;
}
