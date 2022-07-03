/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:18:37 by lrandria          #+#    #+#             */
/*   Updated: 2021/06/23 19:18:37 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_suffix(t_btree *node, void (*apply_f)(void *))
{
	if (node == NULL)
		return ;
	btree_apply_suffix(node->left, apply_f);
	btree_apply_suffix(node->right, apply_f);
	apply_f(node->content);
}
