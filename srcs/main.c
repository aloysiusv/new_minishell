/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:10:56 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 21:58:59 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned short	g_exit = 0;

static int	only_blanks(char *cmdline)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!cmdline)
		return (1);
	while (cmdline && cmdline[i])
	{
		if (ft_isset(cmdline[i], ALL_SPACES) == 1)
			count++;
		i++;
	}
	if (count == i)
		return (1);
	return (0);
}

static void	parsing(t_shell *sh)
{
	if (get_lst_chars(sh->cmdline, &sh->chars) == -1)
		return ;
	get_lst_tokens(sh->chars, &sh->tokens);
	get_lst_expanded(&sh->tokens, sh->env_var);
	if (syntax_errors(sh->tokens) == -1)
		return ;
	sh->nb_cmds = get_tab_cmds(&sh->cmds, &sh->tokens);
}

static void	minishell(t_env **env)
{
	t_shell		sh;
	t_builtinp	builtin;

	sh.cmdline = readline(PROMPT);
	while (sh.cmdline)
	{
		if (!only_blanks(sh.cmdline))
		{
			add_history(sh.cmdline);
			parsing(&sh);
			builtin = is_builtin(sh.cmds);
			if (sh.nb_cmds == 1 && builtin)
				launch_builtin(sh.cmds, env, builtin);
			else
				launch_commands(sh.nb_cmds, sh.cmds, env);
			t_node_delete_lst(&sh.chars);
			t_node_delete_lst(&sh.tokens);
			delete_cmds_tab(&sh.cmds);
		}
		free(sh.cmdline);
		sh.cmdline = readline(PROMPT);
	}
}

int	main(int ac, char *av[], char *ep[])
{
	t_env	*env_ptr;

	(void)ac;
	(void)av;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	env_ptr = create_lst_env(ep);
	minishell(&env_ptr);
	delete_lst_env(&env_ptr);
	rl_clear_history();
	return (g_exit);
}
