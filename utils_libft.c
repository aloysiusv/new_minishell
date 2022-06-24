/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:52:10 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/23 13:58:13 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// size_t	ft_strlcpy(char *dst, const	char *src, size_t size)
// {
// 	size_t	i;

// 	i = 0;
// 	while (src[i] && i + 1 < size)
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	if (size > 0)
// 		dst[i] = '\0';
// 	return (ft_strlen(src));
// }

// static size_t	slen(unsigned int start, size_t len, size_t size)
// {
// 	if (size < start)
// 		return (0);
// 	else if (size - start < len)
// 		return (size - start);
// 	else
// 		return (len);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*new_str;
// 	size_t	i;
// 	size_t	size;

// 	if (s == 0)
// 		return (0);
// 	size = ft_strlen(s);
// 	new_str = (char *)malloc(sizeof(char) * (slen(start, len, size) + 1));
// 	if (new_str == 0)
// 		return (NULL);
// 	i = 0;
// 	if (start < size)
// 	{
// 		while (s[i + start] && i < len)
// 		{
// 			new_str[i] = s[i + start];
// 			i++;
// 		}
// 	}
// 	new_str[i] = '\0';
// 	return (new_str);
// }

int	ft_isset(char c, char const *my_set)
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

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while ((s1[i] || s2[i]) && i < n)
// 	{
// 		if (s1[i] != s2[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 		i++;
// 	}
// 	return (0);
// }

// void	ft_putstr_fd(char *s, int fd)
// {
// 	if (s == 0)
// 		return ;
// 	write(fd, s, ft_strlen(s));
// }
