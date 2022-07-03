/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 00:37:48 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 19:54:58 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_var(char const *s)
{
	char	**new_arr;
	size_t	size;

	if (!s)
		return (0);
	new_arr = ft_calloc(3, sizeof(char *));
	if (!new_arr)
		return (NULL);
	size = ft_strclen(s, "=");
	new_arr[0] = malloc(sizeof(char) * (size + 1));
	if (new_arr[0] == NULL)
		return (free(new_arr), NULL);
	ft_strlcpy(new_arr[0], s, size + 1);
	new_arr[1] = ft_strdup(s + size + 1);
	if (new_arr[1] == NULL)
		return (ft_free_strs(new_arr), NULL);
	return (new_arr);
}

t_env	*create_lst_env(char **env)
{
	t_env	*head;
	t_env	*node;
	char	**keyvalue;
	size_t	i;

	if (!*env)
		return (NULL);
	head = NULL;
	i = 0;
	while (env[i])
	{
		keyvalue = split_var(env[i]);
		if (keyvalue == NULL || *keyvalue == NULL)
			return (delete_lst_env(&head), NULL);
		node = create_node(keyvalue[0], keyvalue[1]);
		if (node == NULL)
			return (ft_free_strs(keyvalue), delete_lst_env(&head), NULL);
		push_back_node(&head, node);
		free(keyvalue);
		i++;
	}
	return (head);
}
