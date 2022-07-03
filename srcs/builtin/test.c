/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:51:29 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/01 11:01:01 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_test(t_cmd *cmd, t_env **env)
{
	const char	str[] = "Hello World!\n";

	(void)cmd;
	(void)env;
	write(1, str, ft_strlen(str));
	return (0);
}
