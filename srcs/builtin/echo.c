/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 19:49:32 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 02:05:18 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_only_n(char *s, char n)
{
	size_t	i;

	i = 1;
	while (s && s[i] != '\0')
	{
		if (s[i] != n)
			return (-1);
		i++;
	}
	return (0);
}

int	builtin_echo(t_cmd *cmd, t_env **env)
{
	size_t	i;
	size_t	has_n;

	(void)env;
	i = 1;
	has_n = 0;
	if (get_tab_size(cmd->command) > 1)
	{
		while (cmd->command[i] && ft_strncmp(cmd->command[i], "-n", 2) == 0
			&& check_only_n(cmd->command[i], 'n') == 0)
		{
			has_n++;
			i++;
		}
		while (cmd->command[i])
		{
			ft_putstr_fd(cmd->command[i], 1);
			if (cmd->command[i + 1] && cmd->command[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (has_n == 0)
		write(1, "\n", 1);
	return (0);
}
