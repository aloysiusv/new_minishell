/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 16:28:41 by lrandria          #+#    #+#             */
/*   Updated: 2021/06/10 20:07:15 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	i;

	if (s1 == 0 || s2 == 0)
		return (0);
	new_s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_s == 0)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_s[i] = ((char *)s1)[i];
		i++;
	}
	while (*s2)
	{
		new_s[i] = *s2;
		i++;
		s2++;
	}
	new_s[i] = '\0';
	return (new_s);
}
