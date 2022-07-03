/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:58:45 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 15:09:39 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirect(t_cmd *cmd, t_env **env)
{
	size_t			i;
	size_t			j;
	const t_type	*types = (t_type []){
	{handle_infile, INFILE},
	{handle_limiter, LIMITER},
	{handle_outfile, OUTFILE},
	{handle_outfile_a, OUTFILE_A}};

	i = 0;
	while (i < cmd->nb_files)
	{
		j = 0;
		while (j < 4)
		{
			if (types[j].type == cmd->files[i].type)
				if (types[j].handler(cmd, env, cmd->files[i].name) == -1)
					return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	redirect_command(int fdin, int fdout)
{
	if (dup2(fdin, STDIN_FILENO) == -1)
		return (-1);
	if (dup2(fdout, STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}
