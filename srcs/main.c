/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:10:56 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 03:16:07 by lrandria         ###   ########.fr       */
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

static int	parsing(t_shell *sh)
{
	if (get_lst_chars(sh->cmdline, &sh->chars) == -1)
		return (t_node_delete_lst(&sh->chars), -1);
	get_lst_tokens(sh->chars, &sh->tokens);
	get_lst_expanded(&sh->tokens, *sh->env_var);
	if (syntax_errors(sh->tokens) == -1)
	{
		t_node_delete_lst(&sh->chars);
		t_node_delete_lst(&sh->tokens);
		return (-1);
	}
	sh->nb_cmds = get_tab_cmds(sh);
	return (0);
}

static int	minishell(t_env **env)
{
	t_shell		sh;
	t_builtinp	builtin;
	bool		exit;

	exit = false;
	sh.env_var = env;
	sh.cmdline = readline(PROMPT);
	while (sh.cmdline)
	{
		if (!only_blanks(sh.cmdline))
		{
			add_history(sh.cmdline);
			if (parsing(&sh) == -1)
			{
				free(sh.cmdline);
				sh.cmdline = readline(PROMPT);
				continue ;
			}
			builtin = is_builtin(sh.cmds);
			if (sh.nb_cmds == 1 && builtin)
			{
				launch_builtin(sh.cmds, env, builtin);
				exit = (*sh.cmds).exit;
			}
			else
				launch_commands(&sh, env);
			t_node_delete_lst(&sh.chars);
			t_node_delete_lst(&sh.tokens);
			delete_cmds_tab(&sh);
		}
		free(sh.cmdline);
		if (exit)
			return (1);
		sh.cmdline = readline(PROMPT);
	}
	return (0);
}

int	main(int ac, char *av[], char *ep[])
{
	t_env	*env_ptr;

	(void)ac;
	(void)av;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	env_ptr = create_lst_env(ep);
	if (!minishell(&env_ptr))
		ft_putstr_fd("exit\n", 2);
	delete_lst_env(&env_ptr);
	rl_clear_history();
	return (g_exit);
}
