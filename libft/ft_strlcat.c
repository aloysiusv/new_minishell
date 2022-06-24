/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:09:19 by lrandria          #+#    #+#             */
/*   Updated: 2021/06/10 20:03:05 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const	char *src, size_t size)
{
	size_t	dst_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	i = 0;
	while (src[i] && i + dst_len + 1 < size)
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	if (size > 0)
		dst[i + dst_len] = '\0';
	if (size < dst_len)
		return (size + ft_strlen(src));
	return (dst_len + ft_strlen(src));
}
