/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:39:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 14:39:40 by lrandria         ###   ########.fr       */
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

char	*lst_to_str(t_node *lst)
{
	char	*line;
	t_node	*iterator;

	iterator = lst;
	if (ft_lstsize_2(lst) == 1)
		line = ft_strdup(iterator->word);
	else
	{
		while (iterator && iterator->next)
		{
			line = ft_strjoin(iterator->word, iterator->next->word);
			if (!line)
				return (delete_lst(&lst), NULL);
			iterator = iterator->next;
		}
	}
	return (line);
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
