/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:39:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 15:14:19 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_tab_size(char **tab)
{
	size_t	i;

	if (!tab)
		return (0);
	i = 0;
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

size_t  get_nb_types(t_node *tokens, int type)
{
    t_node  *iterator;
    size_t  nb_types;

    iterator = tokens;
	nb_types = 0;
    while (iterator)
    {
        if (iterator->type == type)
			nb_types++;
        iterator = iterator->next;
    }
	return (nb_types);
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
