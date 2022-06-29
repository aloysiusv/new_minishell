/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:39:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/29 20:22:09 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_tab_size(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
	{
		return (0);
	}
	while (tab[i])
		i++;
	return (i);
}

char	**lst_to_tab(t_node *lst)
{
	size_t	i;
	size_t	size;
	char	**tab;
	t_node	*iterator;

	size = ft_lstsize_2(lst);
	i = 0;
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	iterator = lst;
	while (iterator)
	{
		tab[i++] = ft_strdup(iterator->word);
		iterator = iterator->next;
	}
	tab[i] = NULL;
	return (tab);
}

t_node	*get_lst_tail(t_node *head)
{
	t_node	*tail;

	tail = head;
	while (tail->next)
		tail = tail->next;
	return (tail);
}

size_t	ft_lstsize_2(t_node *head)
{
	size_t	size;
    t_node  *iterator;

	if (!head)
		return (0);
    iterator = head;
	size = 0;
	while (iterator)
	{
		iterator = iterator->next;
		size++;
	}
	return (size);
}

int	is_valid_input(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}
