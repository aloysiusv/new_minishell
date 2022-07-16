/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 20:05:02 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 08:54:22 by wmachrou         ###   ########.fr       */
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
