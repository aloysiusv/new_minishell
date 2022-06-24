/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:15:21 by lrandria          #+#    #+#             */
/*   Updated: 2021/06/09 15:17:10 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	int_len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*n_ascii;
	unsigned int	nb;
	size_t			len;

	len = int_len(n);
	n_ascii = (char *)malloc(sizeof(char) * (len + 1));
	if (n_ascii == 0)
		return (0);
	n_ascii[len] = '\0';
	nb = n;
	if (n < 0)
	{
		nb = -n;
		n_ascii[0] = '-';
	}
	if (n == 0)
		n_ascii[0] = '0';
	while (nb)
	{
		n_ascii[len - 1] = nb % 10 + '0';
		nb /= 10;
		len--;
	}
	return (n_ascii);
}
