/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:50:30 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/29 22:58:55 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_cmd(t_cmd cmd)
{
	if (cmd.tokens)
		delete_lst(&cmd.tokens);
	if (cmd.exec_path)
		free(cmd.exec_path);
	if (cmd.command)
		free_tab(cmd.command);
	if (cmd.outfiles)
		free_tab(cmd.outfiles);
}

void	delete_cmds_tab(t_cmd *cmds, size_t	nb_cmds)
{
	size_t	i;

	if (!cmds)
		return ;
	i = 0;
	while (i < nb_cmds)
	{
		delete_cmd(cmds[i]);
		i++;
	}
	free(cmds);
}
