/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:22:59 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 22:33:53 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_cmd *c, t_shell *sh)
{
	(void)sh;
	if (!c || !c->command)
		return ;
	printf("command[%s]\n", c->command[0]);
    if (!ft_strcmp(c->command[0], "echo"))
		ft_echo(c);
	// else if (!ft_strcmp(token->word, "cd"))
	// 	ft_cd(cmd, env);
	// else if (!ft_strcmp(token->word, "pwd"))
	// 	ft_pwd(cmd, env);
	// else if (!ft_strcmp(token->word, "env"))
	// 	ft_env(env);
	// else if (!ft_strcmp(token->word, "export"))
	// 	ft_export(&env, cmd);
	// else if (!ft_strcmp(token->word, "unset"))
	// 	ft_unset(&env, cmd);
    // else if (!ft_strcmp(token->word, "exit"))
	// 	ft_exit(&env, cmd);
}
