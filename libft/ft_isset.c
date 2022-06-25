/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:36:23 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/25 21:20:27 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isset(char c, char const *my_set)
{
	size_t	i;

	i = 0;
	if (!my_set)
		return (0);
	while (my_set[i])
	{
		if (c == my_set[i])
			return (1);
		i++;
	}
	return (0);
}
