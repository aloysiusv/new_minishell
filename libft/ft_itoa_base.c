/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 21:47:47 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/30 16:56:31 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int n, const char *base, size_t len_base)
{
	char			*nbr;
	size_t			len;
	unsigned int	nb;

	len = ft_nbrlen_base(n, len_base);
	nbr = (char *)malloc(len + 1);
	if (nbr == 0)
		return (0);
	nbr[len] = 0;
	nb = n;
	if (n < 0)
		nb = -n;
	while (len--)
	{
		nbr[len] = base[nb % len_base];
		nb /= len_base;
	}
	if (n < 0)
		nbr[0] = '-';
	return (nbr);
}
