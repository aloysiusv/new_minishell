/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:19:29 by lrandria          #+#    #+#             */
/*   Updated: 2021/04/15 21:19:29 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*d;

	d = (char *)malloc(ft_strlen(s) + 1);
	if (d == 0)
		return (0);
	ft_strcpy(d, s);
	return (d);
}
