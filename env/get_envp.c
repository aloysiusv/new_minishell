/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:03:10 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/28 15:46:18 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **get_envp(char **env)
{
	size_t	i;
	size_t  size;
	char    **my_env;

	size = get_tab_size(env);
	my_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!my_env)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		my_env[i] = ft_strdup(env[i]);
		if (!my_env[i])
		{
			free_prev(my_env, i);
			return (NULL);
		}
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}
