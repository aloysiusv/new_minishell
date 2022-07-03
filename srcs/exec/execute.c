/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 00:16:05 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 19:44:04 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_empty_command(t_cmd *cmd, t_env **env)
{
	if (cmd->command == NULL)
	{
		delete_lst_env(env);
		// rl_clear_history();
		exit(0);
	}
}

static void	execute_builtin(t_cmd *cmd, t_env **env)
{
	t_builtinp	builtin;
	int			status;

	builtin = is_builtin(cmd);
	if (builtin)
	{
		status = builtin(cmd, env);
		delete_lst_env(env);
		exit(status);
	}
}

static char	*resolve_command(char *command_name, char *path_value, t_env **env)
{
	char	*command;
	t_stat	buf;

	if (path_value && !ft_strnstr(command_name, "/", ft_strlen(command_name)))
	{
		command = resolve_path(command_name, path_value);
		if (command == NULL)
		{
			print_error(command_name, "command not found", 0);
			delete_lst_env(env);
			exit(127);
		}
	}
	else
	{
		command = command_name;
		if (!stat(command, &buf) && S_ISDIR(buf.st_mode))
		{
			print_error(command_name, NULL, EISDIR);
			delete_lst_env(env);
			exit(126);
		}
	}
	return (command);
}

void	execute_command(t_cmd *cmd, t_env **env)
{
	char	*command;
	char	**envp;

	handle_empty_command(cmd, env);
	execute_builtin(cmd, env);
	command = resolve_command(cmd->command[0], find_env(*env, "PATH"), env);
	envp = convert_env(*env);
	if (execve(command, cmd->command, envp) == -1)
	{
		print_error(command, NULL, errno);
		if (command != cmd->command[0])
			free(command);
		ft_free_strs(envp);
		delete_lst_env(env);
		// rl_clear_history();
		if (errno == ENOENT)
			exit(127);
		exit(126);
	}
}
