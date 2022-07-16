/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:33:10 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 09:11:27 by wmachrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*line_expanded(char *line, t_env *env)
{
	t_node	*chars;
	t_node	*tokens;
	char	*new_line;

	if (hrdoc_get_lst_chars(line, &chars) == -1)
	{
		t_node_delete_lst(&chars);
		return (line);
	}
	hrdoc_get_lst_tokens(chars, &tokens);
	hrdoc_get_lst_expanded(&tokens, env);
	new_line = lst_to_str(tokens);
	t_node_delete_lst(&chars);
	t_node_delete_lst(&tokens);
	if (new_line)
		return (free(line), new_line);
	return (line);
}

static void	execute_heredoc(char *limit, t_cmd *cmd, t_env **env, t_fds pipefds)
{
	char	*line;

	close(pipefds[0]);
	signal(SIGINT, SIG_DFL);
	line = readline(PROMPT_HEREDOC);
	while (!line || ft_strcmp(line, limit))
	{
		if (line)
		{
			if (*env && find_char(line, '$') == 1
				&& cmd->files[cmd->index_files].quote == false)
				line = line_expanded(line, *env);
			write(pipefds[1], line, ft_strlen(line));
		}
		write(pipefds[1], "\n", 1);
		if (line)
			free(line);
		line = readline(PROMPT_HEREDOC);
	}
	free(line);
	delete_fork(cmd->sh, env, 0);
}

int	heredoc(char *limiter, t_cmd *cmd, t_env **env)
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
		execute_heredoc(limiter, cmd, env, pipefds);
	close(pipefds[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_signal);
	if (WIFSIGNALED(status))
		return (-1);
	return (pipefds[0]);
}
