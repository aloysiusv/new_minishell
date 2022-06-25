/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:49:47 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 16:40:33 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_env_paths(t_shell *sh, t_command *cmd)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], "PATH=", 5) == 0)
		{
			tmp = ft_substr(sh->envp[i], 5, ft_strlen(sh->envp[i]));
			if (tmp == NULL)
				oops_crash(cmd, "minishell: error: 'malloc' failed\n");
			sh->all_paths = ft_split(tmp, ':');
			if (sh->all_paths == NULL)
			{
				free(tmp);
				oops_crash(cmd, "minishell: error:  'malloc' failed\n");
			}
			free(tmp);
		}
		i++;
	}
	if (sh->all_paths == NULL)
		return ;
}

static void	add_slash_to_path(t_shell *sh, t_command *cmd, size_t i)
{
	char	*tmp;

	tmp = ft_strjoin(sh->all_paths[i], "/");
	if (sh->all_paths[i][ft_strlen(sh->all_paths[i]) - 1] != '/')
		cmd->exec_path = ft_strjoin(tmp, cmd->command[0]);
	else
		cmd->exec_path = ft_strjoin(sh->all_paths[i], cmd->command[0]);
	if (cmd->exec_path == NULL)
	{
		free(tmp);
		oops_crash(cmd, "pipex: error: 'malloc' failed\n");
	}
	free(tmp);
}

void	execute_env_var_command(t_shell *sh, t_command *cmd)
{
	size_t	i;

	create_env_paths(sh, cmd);
	i = 0;
	while (sh->all_paths[i])
	{
		add_slash_to_path(sh, cmd, i);
		if (access(cmd->exec_path, F_OK | X_OK) == 0)
		{
			if (execve(cmd->exec_path, cmd->command, sh->envp) == -1)
				oops_crash(cmd, "minishell: error: execve system call failed\n");
		}
		free(cmd->exec_path);
		cmd->exec_path = NULL;
		i++;
	}
}

static void	check_extra_spaces(t_command *cmd)
{
	size_t	last_char;

	last_char = ft_strlen(cmd->full_line) - 1;
	if (cmd->full_line[0] == ' ' || cmd->full_line[last_char] == ' ')
		display_cmd_error(cmd, cmd->full_line);
}

void	execute_command(t_shell *sh, t_command *cmd)
{
	check_extra_spaces(cmd);
	cmd->command = ft_split(cmd->full_line, ' ');
	if (cmd->command == NULL)
		return ;
	if (find_char(cmd->command[0], "/") == 1)
	{
		if (access(cmd->command[0], F_OK | X_OK) == 0)
			if (execve(cmd->command[0], cmd->command, sh->envp) == -1)
				oops_crash(cmd, "minishell: error: execve system call failed\n");
		display_cmd_error(cmd, cmd->full_line);
	}
	else
		execute_env_var_command(sh, cmd);
	display_cmd_error(cmd, cmd->full_line);
}