/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmachrou <wmachrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:00:21 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 17:03:27 by wmachrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_cmd(size_t nb_cmds, t_cmd *cmds, size_t i)
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
		{
			cmds[i].status = WTERMSIG(status);
			if (!i)
				write(1, "\n", 1);
		}
		i++;
	}
	if (nb_cmds)
		g_exit = cmds[nb_cmds - 1].status;
}

int	launch_commands(t_shell *s, t_env **e)
{
	size_t	i;
	pid_t	pid;

	i = -1;
	while (++i < s->nb_cmds)
	{
		if (pipe_cmd(s->nb_cmds, s->cmds, i) || handle_redirect(s->cmds + i, e))
			return (EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			return (EXIT_FAILURE);
		else if (pid == 0)
		{
			if (redirect_command(s->cmds[i].fdin, s->cmds[i].fdout) == -1)
				return (EXIT_FAILURE);
			close_fds(s->nb_cmds, s->cmds);
			execute_command(s, i, e);
		}
		s->cmds[i].pid = pid;
	}
	close_fds(s->nb_cmds, s->cmds);
	signal(SIGINT, SIG_IGN);
	wait_commands(s->nb_cmds, s->cmds);
	signal(SIGINT, handle_signal);
	return (EXIT_SUCCESS);
}
