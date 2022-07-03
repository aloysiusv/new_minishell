/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:58:40 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 14:47:13 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code = 0;

static void	exec(t_shell *sh)
{
	exec_builtin(sh->cmds, sh);
	exec_hrdoc(sh->cmds, sh);
	// exec_simple_cmd(sh->tokens);
	// exec_multi_cmds(sh->tokens);
}

static int	parsing(t_shell *sh)
{
	if (get_lst_chars(sh->cmdline, &sh->chars) == -1)
		return (delete_lst(&sh->chars), -1);
	get_lst_tokens(sh->chars, &sh->tokens);
	get_lst_expanded(&sh->tokens, sh->env_var);
	if (syntax_errors(sh->tokens) == -1)
	{
		delete_lst(&sh->chars);
		delete_lst(&sh->tokens);
		return (-1);
	}
	get_tab_cmds(&sh->cmds, &sh->tokens);
	return (0);
	// t_node *iterator = sh->tokens;
	// while (iterator)
	// {
	// 	printf("[%s]	=> in_squotes [%d] || in_dquotes [%d] || type [%d]\n",
	// 		iterator->word, iterator->in_squotes,
	// 			iterator->in_dquotes, iterator->type);
	// 	iterator = iterator->next;
	// }
	// if (syntax_errors(sh->tokens) == -1)
	// 	return ;
}

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

static void	mini_loop(t_shell *sh)
{
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		sh->cmdline = readline(PROMPT);
		if (!*sh->cmdline || only_blanks(sh->cmdline) == 1)
		{
			free(sh->cmdline);
			continue ;
		}
		if (ft_strlen(sh->cmdline) > 0)
		{
			add_history(sh->cmdline);
			if (parsing(sh) == -1)
				continue ;
			exec(sh);
			delete_lst(&sh->chars);
			delete_lst(&sh->tokens);
			delete_cmds_tab(&sh->cmds);
		}
		if (sh->cmdline[0] == 'q')
			break ;
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
	sh->envp = get_envp(envp);
	sh->env_var = create_lst_env(envp);
	mini_loop(sh);
	free_shell(sh);
	return (0);
}
