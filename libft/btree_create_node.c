/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:59:13 by lrandria          #+#    #+#             */
/*   Updated: 2021/06/23 18:59:13 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*btree_create_node(void *content)
{
	t_btree			*node;

	node = (t_btree *)malloc(sizeof(t_btree));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
