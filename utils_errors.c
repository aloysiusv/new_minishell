/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:38:57 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/26 02:20:19 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	oops_crash(t_shell *shell, char *error_message, int exit_code)
{
	ft_putstr_fd("minishell: error: ", 2);
	ft_putstr_fd(error_message, 2);
	free_shell(shell);
	exit(exit_code);
}