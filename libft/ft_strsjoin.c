/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:26:30 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 13:59:58 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_str(char **strs, char *sep)
{
	size_t			count;
	size_t			i;

	count = 0;
	i = 0;
	while (strs[i])
		count += ft_strlen(strs[i++]);
	return (count + ft_strlen(sep) * (i - 1));
}

char	*ft_strsjoin(char **strs, char *sep)
{
	char			*str;
	size_t			i;

	str = (char *)malloc(sizeof(char) * (count_str(strs, sep) + 1));
	if (str == 0)
		return (0);
	*str = 0;
	i = 0;
	while (strs[i])
	{
		if (i)
			ft_strcat(str, sep);
		ft_strcat(str, strs[i++]);
	}
	return (str);
}
