/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 19:07:30 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 03:15:51 by lrandria         ###   ########.fr       */
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
	FILENAME,
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

typedef struct s_node
{
	char			charac;
	char			*word;
	int				type;
	bool			in_squotes;
	bool			in_dquotes;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct s_operator
{
	int				type;
	char			ope;
}					t_operator;

							/* ENV VARIABLES */

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

							/* EXECUTION */

/* Stock redirections */
typedef struct s_file
{
	char			*name;
	int				type;
	bool			quote;
}					t_file;

struct s_shell;

/* Stock every cmds with their args, redirs, path... */
typedef struct s_cmd
{
	t_node			*tokens;
	t_file			*files;
	size_t			index;
	size_t			index_files;
	size_t			nb_cmds;
	size_t			nb_files;
	char			*exec_path;
	char			**command;
	pid_t			pid;
	int				status;
	int				fdin;
	int				fdout;
	bool			exit;
	struct s_shell	*sh;	
}					t_cmd;

							/* SHELL DATA */

typedef struct s_shell
{
	char			*cmdline;
	char			**envp;
	char			**all_paths;
	t_env			**env_var;
	t_node			*chars;
	t_node			*tokens;
	t_cmd			*cmds;
	size_t			nb_cmds;
}					t_shell;

							/* UTILS_EXEC */

/* Identify built-ins */
typedef struct s_builtin
{
	int				(*builtin)(t_cmd *, t_env **);
	char			*name;
}					t_builtin;

/* Manipulate file list */
typedef struct s_type 
{
	int				(*handler)(t_cmd *, t_env **, char *);
	int				type;
}					t_type; 

							/* ALIASES */

typedef DIR*			t_dirp;
typedef struct dirent*	t_direntp;
typedef struct stat		t_stat;
typedef int				t_fds[2];
typedef int				(*t_builtinp)(t_cmd *, t_env **);

#endif