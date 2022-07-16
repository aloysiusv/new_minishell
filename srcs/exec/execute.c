/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmachrou <wmachrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 00:16:05 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 16:57:56 by wmachrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_fork(t_shell *sh, t_env **env, size_t status)
{
	t_node_delete_lst(&sh->chars);
	t_node_delete_lst(&sh->tokens);
	delete_cmds_tab(sh);
	delete_lst_env(env);
	rl_clear_history();
	exit(status);
}

static void	handle_empty_command(t_shell *sh, size_t i, t_env **env)
{
	if (sh->cmds[i].command == NULL || sh->cmds[i].command[0] == NULL)
		delete_fork(sh, env, g_exit);
}

static void	execute_builtin(t_shell *sh, size_t i, t_env **env)
{
	t_builtinp	builtin;
	int			status;

	builtin = is_builtin(sh->cmds + i);
	if (builtin)
	{
		status = builtin(sh->cmds + i, env);
		delete_fork(sh, env, status);
	}
}

static char	*resolve_command(t_shell *sh, size_t i, char *path, t_env **env)
{
	char	*command;
	t_stat	buf;

	if (path && !ft_strnstr(
			sh->cmds[i].command[0], "/", ft_strlen(sh->cmds[i].command[0])))
	{
		command = resolve_path(sh->cmds[i].command[0], path);
		if (command == NULL)
		{
			print_error(sh->cmds[i].command[0], "command not found", 0);
			delete_fork(sh, env, 127);
		}
	}
	else
	{
		command = sh->cmds[i].command[0];
		if (!stat(command, &buf) && S_ISDIR(buf.st_mode))
		{
			print_error(sh->cmds[i].command[0], NULL, EISDIR);
			delete_fork(sh, env, 126);
		}
	}
	return (command);
}

void	execute_command(t_shell *sh, size_t i, t_env **env)
{
	char	*command;
	char	**envp;

	signal(SIGINT, SIG_DFL);
	handle_empty_command(sh, i, env);
	execute_builtin(sh, i, env);
	command = resolve_command(sh, i, find_env(*env, "PATH"), env);
	envp = convert_env(*env);
	if (execve(command, sh->cmds[i].command, envp) == -1)
	{
		print_error(command, NULL, errno);
		if (command != sh->cmds[i].command[0])
			free(command);
		ft_free_strs(envp);
		t_node_delete_lst(&sh->chars);
		t_node_delete_lst(&sh->tokens);
		delete_cmds_tab(sh);
		delete_lst_env(env);
		rl_clear_history();
		if (errno == ENOENT)
			exit(127);
		exit(126);
	}
}
