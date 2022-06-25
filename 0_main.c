/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:58:40 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/25 12:48:51 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code = 0;

static void	parsing(t_shell *sh)
{
	get_lst_chars(sh->cmdline, &sh->chars);
	get_lst_tokens(sh->chars, &sh->tokens);
	syntax_errors(sh, sh->tokens);
	expansions(sh);
	// get_lst_cmds(sh);
}

static void	mini_loop(t_shell *sh)
{
	while (1)
	{
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, handle_signals);
		sh->cmdline = readline(PROMPT);
		if (!sh->cmdline)
			free(sh->cmdline);
		if (sh->cmdline && ft_strlen(sh->cmdline) > 0)
			add_history(sh->cmdline);
		parsing(sh);
		execute(sh);
		free(sh->tokens);
		free(sh->cmdline);
	}
}

int		main(int ac, char *av[], char *envp[])
{
	t_shell	*sh;

	(void)av;
	if (ac > 1)
		oops_crash(NULL, "Too many arguments.\n", 127);
	sh = (t_shell *)ft_calloc(1, sizeof(t_shell));
	if (!sh)
		return (EXIT_FAILURE);
	sh->envp = create_lst_env(envp);
	mini_loop(sh);
	free_shell(sh);
	return (0);
}
