/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmachrou <wmachrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:32:53 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 15:54:30 by wmachrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_save(t_fds stdfds)
{
	stdfds[0] = dup(STDIN_FILENO);
	if (stdfds[0] == -1)
		return (-1);
	stdfds[1] = dup(STDOUT_FILENO);
	if (stdfds[1] == -1)
		return (-1);
	return (0);
}

static int	redirect_reset(int fdin, int fdout)
{
	if (dup2(fdin, STDIN_FILENO) == -1)
		return (-1);
	if (dup2(fdout, STDOUT_FILENO) == -1)
		return (-1);
	close(fdin);
	close(fdout);
	return (0);
}

int	launch_built(t_cmd *cmd, t_env **env, t_builtinp builtin)
{
	t_fds	stdfds;

	if (handle_redirect(cmd, env))
		return (EXIT_FAILURE);
	if (redirect_save(stdfds))
		return (EXIT_FAILURE);
	if (redirect_command(cmd->fdin, cmd->fdout))
		return (EXIT_FAILURE);
	g_exit = builtin(cmd, env);
	if (redirect_reset(stdfds[0], stdfds[1]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_builtinp	is_builtin(t_cmd *cmd)
{
	size_t			i;
	const t_builtin	builtins[] = {
	{builtin_echo, "echo"}, {builtin_cd, "cd"}, {builtin_pwd, "pwd"},
	{builtin_export, "export"}, {builtin_unset, "unset"},
	{builtin_env, "env"}, {builtin_exit, "exit"}};

	if (!cmd || !cmd->command || !cmd->command[0])
		return (NULL);
	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(builtins[i].name, cmd->command[0]))
			return (builtins[i].builtin);
		i++;
	}
	return (NULL);
}
