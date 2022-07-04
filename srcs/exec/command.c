/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:00:21 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 21:12:00 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_command(size_t nb_cmds, t_cmd *cmds, size_t i)
{
	t_fds	pipefd;

	if (i < nb_cmds - 1)
	{
		if (pipe(pipefd) == -1)
			return (-1);
		cmds[i].fdout = pipefd[1];
		cmds[i + 1].fdin = pipefd[0];
	}
	return (0);
}

static void	close_fds(size_t nb_cmds, t_cmd *cmds)
{
	size_t	i;

	i = 0;
	while (i < nb_cmds)
	{
		if (cmds[i].fdin != -1 && cmds[i].fdin != STDIN_FILENO)
			close(cmds[i].fdin);
		if (cmds[i].fdout != -1 && cmds[i].fdout != STDOUT_FILENO)
			close(cmds[i].fdout);
		i++;
	}
}

static void	wait_commands(size_t nb_cmds, t_cmd *cmds)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < nb_cmds)
	{
		waitpid(cmds[i].pid, &status, 0);
		if (WIFEXITED(status))
			cmds[i].status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			cmds[i].status = WTERMSIG(status);
		i++;
	}
	if (nb_cmds)
		g_exit = cmds[nb_cmds - 1].status;
}

int	launch_commands(t_shell *sh, t_env **env)
{
	size_t	i;
	pid_t	pid;

	i = 0;
	while (i < sh->nb_cmds)
	{
		if (pipe_command(sh->nb_cmds, sh->cmds, i))
			return (EXIT_FAILURE);
		if (handle_redirect(sh->cmds + i, env))
			return (EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			return (EXIT_FAILURE);
		else if (pid == 0)
		{
			if (redirect_command(sh->cmds[i].fdin, sh->cmds[i].fdout) == -1)
				return (EXIT_FAILURE);
			close_fds(sh->nb_cmds, sh->cmds);
			execute_command(sh, i, env);
		}
		sh->cmds[i].pid = pid;
		i++;
	}
	close_fds(sh->nb_cmds, sh->cmds);
	wait_commands(sh->nb_cmds, sh->cmds);
	return (EXIT_SUCCESS);
}
