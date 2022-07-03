/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 23:56:16 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 19:54:04 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	size_env(t_env *vars)
{
	size_t	size;

	size = 0;
	while (vars)
	{
		vars = vars->next;
		size++;
	}
	return (size);
}

char	**convert_env(t_env *vars)
{
	size_t	i;
	size_t	size;
	char	**env;

	size = size_env(vars);
	env = ft_calloc(size + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		env[i] = ft_strsjoin((char *[]){vars->value, vars->key, NULL}, "=");
		if (env[i] == NULL)
			return (ft_free_strs(env), NULL);
		vars = vars->next;
		i++;
	}
	return (env);
}
