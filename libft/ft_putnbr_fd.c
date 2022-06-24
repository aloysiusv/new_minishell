/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 01:16:02 by lrandria          #+#    #+#             */
/*   Updated: 2021/06/07 01:16:02 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	lol;

	if (n < 0)
		lol = -n;
	else
		lol = n;
	if (n < 0)
		write(fd, "-", 1);
	if (lol >= 10)
		ft_putnbr_fd(lol / 10, fd);
	write(fd, &"0123456789"[lol % 10], 1);
}
