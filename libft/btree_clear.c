/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:17:14 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/30 16:56:31 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_clear(t_btree *node, void (*del)(void *))
{
	if (node == NULL)
		return ;
	btree_clear(node->left, del);
	btree_clear(node->right, del);
	if (del != NULL)
		del(node->content);
	free(node);
}
