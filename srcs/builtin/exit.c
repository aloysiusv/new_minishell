/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmachrou <wmachrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:23:34 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 16:13:33 by wmachrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_exit(char *var)
{
	char	*p1;
	char	*p2;
	char	*error;

	p1 = ": exit: ";
	p2 = ": numeric argument required";
	error = ft_strsjoin((char *[]){PROGRAM_NAME, p1, var, p2, "\n", NULL}, "");
	if (error == NULL)
		return ;
	write(2, error, ft_strlen(error));
	free(error);
}

static int	is_number(char *s)
{
	size_t	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i = 1;
	while (s[i])
		if (!ft_isdigit(s[i++]))
			return (0);
	return (1);
}

int	builtin_exit(t_cmd *cmd, t_env **env)
{
	(void)env;
	write(2, "exit\n", ft_strlen("exit\n"));
	if (!cmd->command[1])
	{
		cmd->exit = true;
		return (g_exit);
	}
	if (!is_number(cmd->command[1]))
	{
		cmd->exit = true;
		error_exit(cmd->command[1]);
		return (2);
	}
	if (cmd->command[2] != NULL)
	{
		print_error("exit", "too many arguments", 0);
		return (1);
	}
	cmd->exit = true;
	return ((unsigned char)ft_atoi(cmd->command[1]));
}
