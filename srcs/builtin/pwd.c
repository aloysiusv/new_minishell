/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:03:44 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 12:56:06 by lrandria         ###   ########.fr       */
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

int	builtin_pwd(t_cmd *cmd, t_env **env)
{
	char	cwd[4096 + 2];
	t_stat	buf;

	(void)env;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		print_getcwd_error(errno);
		return (1);
	}
	cwd[ft_strlen(cwd) + 1] = '\0';
	cwd[ft_strlen(cwd)] = '\n';
	if (!fstat(cmd->fdout, &buf))
		write(cmd->fdout, cwd, ft_strlen(cwd));
	return (0);
}
