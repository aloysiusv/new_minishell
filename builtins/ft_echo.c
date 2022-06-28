/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:37:30 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/28 16:25:22 by lrandria         ###   ########.fr       */
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

void	init_echo(size_t *i, size_t *has_n, char ***cmd, t_node *tokens)
{
	*i = 1;
	*has_n = 0;
	*cmd = lst_to_tab(tokens);
	if (!cmd)
		return ;
}

void	ft_echo(t_node	*tokens)
{
	size_t	i;
	size_t	has_n;
	char	**cmd;

	init_echo(&i, &has_n, &cmd, tokens); // norm nonsense :'(
	if (get_tab_size(cmd) > 1)
	{
		while (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0
			&& check_only_n(cmd[i], 'n') == 0)
		{
			has_n++;
			i++;
		}
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1] && cmd[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (has_n == 0)
		write(1, "\n", 1);
	free_tab(cmd);
}
