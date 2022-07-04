/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:32:09 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 03:15:51 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_infile(t_cmd *cmd, t_env **env, char *filename)
{
	(void)env;
	if (cmd->fdin != STDIN_FILENO)
		close(cmd->fdin);
	cmd->fdin = open(filename, O_RDONLY);
	cmd->index_files++;
	if (cmd->fdin == -1)
	{
		print_error(filename, NULL, errno);
		return (-1);
	}
	return (0);
}

int	handle_limiter(t_cmd *cmd, t_env **env, char *limiter)
{
	if (cmd->fdin != STDIN_FILENO)
		close(cmd->fdin);
	cmd->fdin = heredoc(limiter, cmd, env);
	cmd->index_files++;
	if (cmd->fdin == -1)
	{
		write(1, "\n", 1);
		return (-1);
	}
	return (0);
}

int	handle_outfile(t_cmd *cmd, t_env **env, char *filename)
{
	(void)env;
	if (cmd->fdout != STDOUT_FILENO)
		close(cmd->fdout);
	cmd->fdout = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	cmd->index_files++;
	if (cmd->fdout == -1)
	{
		print_error(filename, NULL, errno);
		return (-1);
	}
	return (0);
}

int	handle_outfile_a(t_cmd *cmd, t_env **env, char *filename)
{
	(void)env;
	if (cmd->fdout != STDOUT_FILENO)
		close(cmd->fdout);
	cmd->fdout = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0664);
	cmd->index_files++;
	if (cmd->fdout == -1)
	{
		print_error(filename, NULL, errno);
		return (-1);
	}
	return (0);
}
