/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:38:57 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/28 17:30:05 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	oops_malloc_crash(void *content, t_shell *shell, int exit_code)
{
	ft_putstr_fd("minishell: error: failed 'malloc'\n", 2);
	free (content);
	free_shell(shell);
	exit(exit_code);
}

void	oops_crash(t_shell *shell, char *error_message, int exit_code)
{
	ft_putstr_fd("minishell: error: ", 2);
	ft_putstr_fd(error_message, 2);
	free_shell(shell);
	exit(exit_code);
}

int		print_error(char *error_message, int exit_code)
{
	ft_putstr_fd("minishell: error: ", 2);
	ft_putstr_fd(error_message, 2);
	g_exit_code = exit_code;
	return (g_exit_code);
}