/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:19:14 by lrandria          #+#    #+#             */
/*   Updated: 2021/04/15 21:19:14 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free_split(char **strs, int size)
{
	int				i;

	i = 0;
	while (i < size)
		free(strs[i++]);
	free(strs);
	return (0);
}

static int	count_words(const char *str, char sep)
{
	int				count;
	int				i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] && str[i] != sep)
			count++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (count);
}

static char	*allocate_string(char const *s, char c)
{
	char			*str;
	int				j;

	j = 0;
	while (s[j] && s[j] != c)
		j++;
	str = (char *)malloc(j + 1);
	if (str == 0)
		return (0);
	return (str);
}

static char	**split_words(char const *s, char c, char **strs, int len)
{
	int				i;
	int				j;

	i = 0;
	while (i < len)
	{
		while (*s && *s == c)
			s++;
		strs[i] = allocate_string(s, c);
		if (strs[i] == 0)
			return (ft_free_split(strs, i));
		j = 0;
		while (*s && *s != c)
			strs[i][j++] = *s++;
		strs[i++][j] = 0;
	}
	strs[i] = 0;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char			**strs;
	int				len;

	if (s == 0)
		return (0);
	len = count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (len + 1));
	if (strs == 0)
		return (0);
	if (split_words(s, c, strs, len) == 0)
		return (0);
	return (strs);
}
