/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:39:35 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/25 21:44:31 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>

/* ENV VARIABLES */

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}                   t_env;

/* TOKENISATION */
enum e_type
{
	LITERAL,
	BUILTIN,
	FILENAME,
	COMMAND,
	LIMITER,
	PATH,
	ENV_VAR,
	BLANK,
	SQUOTE,
	DQUOTE,
	RD_INPUT,
	RD_OUTPUT,
	APPEND,
	HRDOC,
	PIPE,
	DOLLAR,
	EQUAL,
};

typedef struct		s_operator
{
	int				type;
	char			ope;
}					t_operator;

typedef struct		s_node
{
	char			charac;
	char			*word;
	int				type;
	bool			in_squotes;
	bool			in_dquotes;
	struct s_node	*prev;
	struct s_node	*next;
}                   t_node;

/* EXECUTION */

typedef struct 			s_command
{
	char				**command;
	char				*full_line;
	char				*exec_path;
	char				*redir;
	int					fdin;
	int					fdout;
	struct s_command	*next;
}						t_command;

typedef struct s_hdoc
{
	int		fdin;
	int		fdout;
	int		fds[2];
	char	*limiter;
	char	*line;
}				t_hdoc;

/* SHELL DATA */

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

#endif