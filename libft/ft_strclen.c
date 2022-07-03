/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:14:33 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/30 16:56:31 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strclen(const char *s, const char *charset)
{
	size_t			i;

	i = 0;
	while (s[i])
	{
		if (ft_ischarset(s[i], charset))
			break ;
		i++;
	}
	return (i);
}
