/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 21:48:55 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/30 16:56:31 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen_base(int n, size_t len_base)
{
	size_t			len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= (int)len_base;
		len++;
	}
	return (len);
}
