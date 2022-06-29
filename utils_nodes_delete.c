/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes_delete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:00:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/29 18:00:34 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_node *node)
{
	if (node->word)
	{
		// printf("Deleting word [%s]\n", node->word);
		free(node->word);
		node->word = NULL;
	}
	if (node)
	{
		free(node);
		node = NULL;
	}
}
