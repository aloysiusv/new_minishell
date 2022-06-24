/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:31:12 by lrandria          #+#    #+#             */
/*   Updated: 2021/06/11 16:37:45 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, char const *my_set)
{
	size_t	i;

	i = 0;
	while (my_set[i])
	{
		if (c == my_set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	if (s1 == 0)
		return (NULL);
	i = 0;
	while (s1[i] && ft_isset(s1[i], set) == 1)
		i++;
	j = ft_strlen(s1) - 1;
	while (s1[i] && i < j && ft_isset(s1[j], set) == 1)
		j--;
	new_s = ft_substr(s1, i, j - i + 1);
	return (new_s);
}
