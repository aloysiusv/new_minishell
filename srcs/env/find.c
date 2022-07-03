/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:00:27 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 16:13:35 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(t_env *vars, char *key)
{
	while (vars)
	{
		if (!ft_strcmp(vars->key, key))
			return (vars->value);
		vars = vars->next;
	}
	return (NULL);
}

void	update_env(t_env *vars, char *key, char *value)
{
	while (vars)
	{
		if (!ft_strcmp(vars->key, key))
		{
			free(vars->value);
			vars->value = value;
			return ;
		}
		vars = vars->next;
	}
}
