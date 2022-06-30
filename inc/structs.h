/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:39:35 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/30 01:13:45 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>

								/* TOKENISATION */
enum e_type
{
	USELESS,
	BLANK,
	LITERAL,
	// FILENAME,
	// CMD,
	// ARGS,
	INFILE,
	LIMITER,
	OUTFILE,
	OUTFILE_A,
	SQUOTE,
	DQUOTE,
	RD_INPUT,
	RD_OUTPUT,
	APPEND,
	HRDOC,
	PIPE,
	DOLLAR,
	DOLLAR_TRAIL,
	EQUAL,
};

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

typedef struct		s_operator
{
	int				type;
	char			ope;
}					t_operator;

							/* ENV VARIABLES */


typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}                   t_env;

							/* EXECUTION */

typedef struct s_file
{
	char	*name;
	int		type;
}			t_file;

typedef struct s_command
{
	t_node				*tokens;
	t_file				*files;
	size_t				index;
	char				*exec_path;
	char				**command;
	int					fdin;
	int					fdout;
	size_t				nb_cmds;
	size_t				nb_files;
}						t_cmd;

							/* SHELL DATA */


typedef struct		s_shell
{
	char			*cmdline;
	char			**envp;
	char			**all_paths;
	t_env			*env_var;
	t_node			*chars;
	t_node			*tokens;
	t_cmd			*cmds;
	size_t			nb_redir;
}					t_shell;

							/* HRDOC */


typedef struct 		s_hdoc
{
	t_shell			*data;
	int				fdin;
	int				fdout;
	int				fds[2];
	char			*limiter;
	char			*line;
	// char	*buffer;
	// char	*eof;
}					t_hdoc;


#endif