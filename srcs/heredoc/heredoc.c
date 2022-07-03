/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:33:10 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 21:59:23 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	line_expanded(char **line, t_env *env)
{
	t_node	*chars;
	t_node	*tokens;

	if (hrdoc_get_lst_chars(*line, &chars) == -1)
	{
		t_node_delete_lst(&chars);	
		return ;
	}
	hrdoc_get_lst_tokens(chars, &tokens);
	hrdoc_get_lst_expanded(&tokens, env);
	free(*line);
	*line = lst_to_str(tokens);
	t_node_delete_lst(&chars);
	t_node_delete_lst(&tokens);
}

static void	execute_heredoc(char *limiter, bool quote, t_env **env, t_fds pipefds)
{
	char	*line;

	(void)env;
	close(pipefds[0]);
	signal(SIGINT, SIG_DFL);
	line = readline(PROMPT_HEREDOC);
	while (!line || ft_strcmp(line, limiter))
	{
		if (line)
		{
			if (find_char(line, '$') == 1 && quote == false)
				line_expanded(&line, *env);
			write(pipefds[1], line, ft_strlen(line));
		}
		write(pipefds[1], "\n", 1);
		free(line);
		line = readline(PROMPT_HEREDOC);
	}
	free(line);
	exit(EXIT_SUCCESS);
}

int	heredoc(char *limiter, bool quote, t_env **env)
{
	t_fds	pipefds;
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
