/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:35:46 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 21:00:19 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_cmd *cmd, t_env **env)
{
	size_t	i;

	i = 1;
	while (cmd->command[i])
	{
		remove_node(env, cmd->command[i]);
		i++;
	}
	return (0);
}
