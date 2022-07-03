/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 12:54:40 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 19:51:19 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_cmd *cmd, t_env **env)
{
	t_stat	buf;
	char	*var;
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		var = ft_strsjoin(
				(char *[]){curr->key, "=", curr->value, "\n", NULL}, "");
		if (var == NULL)
			return (1);
		if (!fstat(cmd->fdout, &buf))
			write(cmd->fdout, var, ft_strlen(var));
		free(var);
		curr = curr->next;
	}
	return (0);
}
