/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 23:37:24 by lrandria          #+#    #+#             */
/*   Updated: 2021/06/10 20:02:17 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	s_len;

	s_len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (s_len + 1));
	if (str == 0)
		return (NULL);
	ft_strlcpy(str, s, s_len + 1);
	return (str);
}
