/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:39:00 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 23:32:02 by lrandria         ###   ########.fr       */
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
# include "lst_cmd.h"

/* Modes to specify when creating nodes */
# define FIRST		0
# define NEXT		1

# define WHITE_SPACES " 	\n\t\v\f\r"

extern int	g_exit_code;

typedef struct		s_shell
{
	char			*cmdline;
	char			**envp;
	char			**all_paths;
	size_t			nb_cmds;
	size_t			nb_redir;
	t_node			*env_var;
}					t_shell;

/* utils_extra_libft.c */
int		ft_isset(char c, char const *my_set);

/* utils_free.c */
void	free_tab(char **tab);
void	free_shell(t_shell *sh);

#endif
