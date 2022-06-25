/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:39:00 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/25 12:39:50 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/libft.h"
# include "lst_env.h"
# include "lst_tokens.h"
# include "lst_commands.h"

# define PROMPT "\033[1;35m~mini$hell~>\033[m "

/* Modes to specify when creating nodes */
# define FIRST		0
# define NEXT		1

# define WHITE_SPACES " 	\n\t\v\f\r"

extern int	g_exit_code;

typedef struct	s_shell
{
	char		*cmdline;
	char		**envp;
	char		**all_paths;
	t_env		*env_var;
	t_node		*chars;
	t_node		*tokens;
	t_command	*cmds;
	size_t		nb_cmds;
	size_t		nb_redir;
}				t_shell;

/* utils_signals.c */
void	handle_signals(int sig);

/* utils_free.c */
void	free_tab(char **tab);
void	free_shell(t_shell *sh);

#endif
