/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:38:57 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 20:02:50 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	p_error(char *error_message, int exit_code)
{
	ft_putstr_fd("minishell: error: ", 2);
	ft_putstr_fd(error_message, 2);
	g_exit = exit_code;
	return (g_exit);
}

void	print_error(const char *file, const char *msg, const int errnum)
{
	char	error[8192];

	*error = '\0';
	ft_strcat(error, PROGRAM_NAME);
	if (file)
	{
		ft_strcat(error, ": ");
		ft_strcat(error, file);
	}
	if (msg)
	{
		ft_strcat(error, ": ");
		ft_strcat(error, msg);
	}
	if (errnum)
	{
		ft_strcat(error, ": ");
		ft_strcat(error, strerror(errnum));
	}
	ft_strcat(error, "\n");
	write(2, error, ft_strlen(error));
}
