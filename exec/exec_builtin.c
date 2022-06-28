/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:22:59 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/28 15:56:23 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_node *tokens, t_env *env)
{
	(void)env;
    if (!ft_strncmp(tokens->word, "echo", 5))
		ft_echo(tokens);
	// else if (!ft_strncmp(token->word, "cd", 3))
	// 	ft_cd(cmd, env);
	// else if (!ft_strncmp(token->word, "pwd", 4))
	// 	ft_pwd(cmd, env);
	// else if (!ft_strncmp(token->word, "env", 4))
	// 	ft_env(env);
	// else if (!ft_strncmp(token->word, "export", 7))
	// 	ft_export(&env, cmd);
	// else if (!ft_strncmp(token->word, "unset", 6))
	// 	ft_unset(&env, cmd);
    // else if (!ft_strncmp(token->word, "exit", 5))
	// 	ft_exit(&env, cmd);
}
