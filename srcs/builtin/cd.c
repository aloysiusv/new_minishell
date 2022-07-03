/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:37:12 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 15:18:30 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_getcwd_error(int errnum)
{
	char	error[256];

	*error = '\0';
	ft_strcat(error, "cd: error retrieving current directory: ");
	ft_strcat(error, "getcwd: cannot access parent directories: ");
	ft_strcat(error, strerror(errnum));
	ft_strcat(error, "\n");
	write(2, error, ft_strlen(error));
}

static char	*resolve_arg(t_cmd *cmd, t_env **env)
{
	char	*arg;
	size_t	args_size;

	args_size = ft_strslen(cmd->command);
	if (args_size > 2)
	{
		print_error("cd", "too many arguments", 0);
		return (NULL);
	}
	if (args_size != 1)
		arg = cmd->command[1];
	else
	{
		arg = find_env(*env, "HOME");
		if (arg == NULL)
		{
			print_error("cd", "HOME not set", 0);
			return (NULL);
		}
	}
	return (arg);
}

int	builtin_cd(t_cmd *cmd, t_env **env)
{
	char	cwd[4096 + 1];
	char	*path;
	char	*arg;

	arg = resolve_arg(cmd, env);
	if (arg == NULL)
		return (1);
	if (arg[0] == '/')
	{
		if (chdir(cmd->command[1]) == -1)
			return (print_error("cd", cmd->command[1], errno), 1);
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			return (print_getcwd_error(errno), 1);
		path = ft_strsjoin((char *[]){cwd, arg, NULL}, "/");
		if (path == NULL)
			return (1);
		if (chdir(path) == -1)
			return (print_error("cd", arg, errno), free(path), 1);
		free(path);
	}
	return (0);
}
