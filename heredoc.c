/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:49:34 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 17:23:02 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	line_expanded(char **line, t_env *env)
{
	t_node	*chars;
	t_node	*tokens;

	hrdoc_get_lst_chars(*line, &chars);
	hrdoc_get_lst_tokens(chars, &tokens);
	hrdoc_get_lst_expanded(&tokens, env);
	*line = lst_to_str(tokens);
	// ft_putstr_fd("expanded [", 2);
	// ft_putstr_fd(*line, 2);
	// ft_putstr_fd("]\n", 2);
	delete_lst(&chars);
	delete_lst(&tokens);
}

static void	execute_heredoc(char *limiter, bool quote, t_env *env, int *pipefds)
{
	char	*line;

	(void)env;
	close(pipefds[0]);
	signal(SIGINT, SIG_DFL);
	line = readline(">");
	while (!line || ft_strcmp(line, limiter))
	{
		if (find_char(line, '$') == 1 && quote == false)
		{
			if (ft_strcmp(limiter, line) == 0)
				break ;
			line_expanded(&line, env);
		}
		write(pipefds[1], line, ft_strlen(line));
		write(pipefds[1], "\n", 1);
		free(line);
		line = readline(">");
	}
	free(line);
	exit(EXIT_SUCCESS);
}

int	heredoc(char *limiter, bool quote, t_env *env)
{
	int	pipefds[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefds) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
		execute_heredoc(limiter, quote, env, pipefds);
	close(pipefds[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_signal);
	if (WIFSIGNALED(status))
		return (-1);
	return (pipefds[0]);
}

void	exec_hrdoc(t_cmd *c, t_shell *sh)
{
	size_t	i;

	i = -1;
	while (++i < c->nb_files)
		if (c->files[i].type == LIMITER)
		{
			if (heredoc(c->files[i].name, c->files[i].quote, sh->env_var) == -1)
			{
				ft_putstr_fd("minishell: error: ", 2);
				ft_putstr_fd("'heredoc' failed\n", 2);
			}
		}
}
