/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:37:30 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 14:55:58 by lrandria         ###   ########.fr       */
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

void	ft_echo(t_cmd *c)
{
	size_t	i;
	size_t	has_n;

	i = 1;
	has_n = 0;
	if (get_tab_size(c->command) > 1)
	{
		while (c->command[i] && ft_strncmp(c->command[i], "-n", 2) == 0
			&& check_only_n(c->command[i], 'n') == 0)
		{
			has_n++;
			i++;
		}
		while (c->command[i])
		{
			ft_putstr_fd(c->command[i], 1);
			if (c->command[i + 1] && c->command[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (has_n == 0)
		write(1, "\n", 1);
}
