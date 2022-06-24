/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra_libft.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:52:10 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 06:33:41 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
