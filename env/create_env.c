/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:02:23 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/25 04:49:33 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_field(char const *s, char sep, int mode)
{
	size_t	size;
	char	*field;
	char	*tmp;

	field = NULL;
	tmp = ft_strchr(s, sep) + 1;
	if (mode == NEXT)
		field = ft_strdup(tmp);
	else if (mode == FIRST)
	{
		size = 0;
		while(s[size] && s[size] != sep)
			size++;
		size += 1;
		field = (char *)malloc(sizeof(char) * (size + 1));
		ft_strlcpy(field, s, size);
	}
	return (field);
}

static char	**split_var(char const *s, char c)
{
	size_t	i;
	char	**new_arr;

	if (!s)
		return (0);
	new_arr = (char **)malloc(sizeof(char *) * 3);
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < 2)
	{
		if (i == 0)
			new_arr[i] = copy_field(s, c, FIRST);
		else
			new_arr[i] = copy_field(s, c, NEXT);
		if (!new_arr)
			return (free_tab(new_arr), NULL);
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

static t_env_var	*init_var(char *var, t_env_var *curr, int mode)
{
	char	**keyvalue;

	keyvalue = split_var(var, '=');
	if (!keyvalue)
		return (NULL);
	if (mode == FIRST)
		return (create_node_var(keyvalue));
	else if (mode == NEXT)
		return(add_bottom_node_var(keyvalue, curr));
	return (NULL);
}

t_env_var		*create_env_lst(char **env, t_env_var **head)
{
	size_t		i;
	t_env_var	*curr;

	if (!env)
		return (NULL);
	*head = init_var(env[0], NULL, FIRST);
	curr = *head;
	i = 1;
	while (env[i])
	{
		curr->next = init_var(env[i], curr, NEXT);
		if (!curr->next)
			return (delete_lst_var(head), NULL);
		i++;
		curr = curr->next;
	}
	return (*head);
}

int main(int ac, char *av[], char *envp[])
{
	t_env_var 	*head;
	t_env_var 	*iterator;

	(void)ac;
	(void)av;
	head = NULL;
	iterator = NULL;
	head = create_env_lst(envp, &head);
	iterator = head;
	while (iterator)
	{
		printf("%s=%s\n", iterator->key, iterator->value);
		iterator = iterator->next;
	}
	delete_specific_node_var(&head, "LS_COLORS");
	printf("=========AFTER DELETING LS COLORS=========\n");
	iterator = head;
	while (iterator)
	{
		printf("%s=%s\n", iterator->key, iterator->value);
		iterator = iterator->next;
	}
	delete_lst_var(&head);
	return (0);
}
