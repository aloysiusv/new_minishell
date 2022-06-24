/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:28:28 by lrandria          #+#    #+#             */
/*   Updated: 2021/06/10 20:07:06 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	slen(unsigned int start, size_t len, size_t size)
{
	if (size < start)
		return (0);
	else if (size - start < len)
		return (size - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	size;

	if (s == 0)
		return (0);
	size = ft_strlen(s);
	new_str = (char *)malloc(sizeof(char) * (slen(start, len, size) + 1));
	if (new_str == 0)
		return (NULL);
	i = 0;
	if (start < size)
	{
		while (s[i + start] && i < len)
		{
			new_str[i] = s[i + start];
			i++;
		}
	}
	new_str[i] = 0;
	return (new_str);
}
