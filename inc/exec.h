/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:09:02 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 16:04:55 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "structs.h"

/* Handle file redirection list */
typedef struct s_type
{
	int		(*handler)(t_cmd *, t_env **, char *);
	int		type;
}			t_type;

/* Handle builtins */
typedef struct s_builtin
{
	int		(*builtin)(t_cmd *, t_env **);
	char	*name;
}			t_builtin;

typedef unsigned short	t_us;
typedef DIR*			t_dirp;
typedef struct dirent*	t_direntp;
typedef struct stat		t_stat;
typedef int				t_fds[2];
typedef int				(*t_builtinp)(t_cmd *, t_env **);

extern t_us				g_exit;

/**
 * @brief    Util functions
 *           Signal handler for SIGINT (Ctrl + C)
 *           Print formated error with a fixed buffer
 */

/**
 * @brief    SIGINT handler
 * 
 * @param    sig                 Signal code (unused)
 */
void		sigint_handler(int sig);

/**
 * @brief    Print formated error on stderr
 * 
 * @param    file                Filename, or NULL
 * @param    msg                 Error message, or NULL
 * @param    errnum              Errno value, or 0
 */
// void		print_error(const char *file, const char *msg, const int errnum);

/**
 * @brief    Environment variables linked list
 *           Create list, delete list, convert list, find element
 * 
 */

// t_env		*create_node(char *key, char *value);
// void		push_back_node(t_env **head, t_env *node);
// void		delete_node(t_env *node);
// void		remove_node(t_env **head, char *key);

/**
 * @brief    Create environment linked list from environment strs
 * 
 * @param    env                 Environment strs
 * @return   t_env*              Environment linked list, or NULL
 */
// t_env		*create_lst_env(char **env);

/**
 * @brief    Delete environment linked list
 * 
 * @param    head                Environment linked list address
 */
// void		delete_lst_env(t_env **head);

/**
 * @brief    Convert environment linked list to environment strs
 * 
 * @param    vars                Environment linked list
 * @return   char**              Environment strs, or NULL
 */
// char		**convert_env(t_env *vars);

/**
 * @brief	Find an environment variable based on key
 * 
 * @param   vars                 Environment as a linked list
 * @param   key                  Key to find in environment
 * @return  char*                Value associated with key, or NULL
 */
// char		*find_env(t_env *vars, char *key);

/**
 * @brief    Builtin functions
 *           echo, cd, pwd, export, unset, env, exit
 *           test builtin should be remove
 * 
 */

int			builtin_test(t_cmd *cmd, t_env **env);
int			builtin_cd(t_cmd *cmd, t_env **env);
int			builtin_env(t_cmd *cmd, t_env **env);

/**
 * @brief    Launch simple builtin and identify builtin functions
 * 
 */

/**
 * @brief    Description
 * 
 * @param    cmd                 Command element pointer
 * @param    env                 Environment linked list address
 * @param    builtin             Function pointer on builtin function
 * @return   int                 EXIT_SUCCESS,
 *                                or EXIT_FAILURE on system call failure
 */
int			launch_builtin(t_cmd *cmd, t_env **env, t_builtinp builtin);

/**
 * @brief    Description
 * 
 * @param    cmd                 Command element pointer
 * @return   t_builtinp          Function pointer on builtin function
 */
t_builtinp	is_builtin(t_cmd *cmd);

/**
 * @brief    Launch multiple commands through pipeline
 * 
 */

/**
 * @brief    Launch a command pipeline with redirections
 * 
 * @param    nb_cmd              Command element array size
 * @param    cmd                 Command element array
 * @param    env                 Environment linked list address
 * @return   int                 EXIT_SUCCESS,
 *                                or EXIT_FAILURE on system call failure
 */
int			launch_commands(size_t nb_cmd, t_cmd *cmd, t_env **env);

/**
 * @brief    Handle files opening and perform redirections
 * 
 */

/**
 * @brief    Handle files opening (call specific file functions - below)
 * 
 * @param    cmd                 Command element pointer
 * @return   int                 0 on success, -1 on failure
 */
int			handle_redirect(t_cmd *cmd, t_env **env);

/**
 * @brief    Redirect command (using dup2() on command fds
 *            opened before with pipe() or open())
 * 
 * @param    fdin                Input FD
 * @param    fdout               Output FD
 * @return   int                 0 on success, -1 on failure
 */
int			redirect_command(int fdin, int fdout);

/**
 * @brief    Open file descriptor and handle errors
 *            (file not found, permission denied)
 * 
 */
int			handle_infile(t_cmd *cmd, t_env **env, char *filename);
int			handle_limiter(t_cmd *cmd, t_env **env, char *filename);
int			handle_outfile(t_cmd *cmd, t_env **env, char *filename);
int			handle_outfile_a(t_cmd *cmd, t_env **env, char *filename);

/**
 * @brief    Handle heredoc with a pipe and handle heredocsignal
 * 
 */
int			heredoc(char *limiter, bool quote, t_env *env);

/**
 * @brief    Execute command code in child process
 *            - builtin execution in multipipe
 *            - search path for command
 *            - execute program based on PATH, absolute or relative path
 * 
 */

/**
 * @brief    Execute a builtin, a command or a program
 * 
 * @param    command_name        Command name
 * @param    command_args        Command arguments
 *                                (containing command name itself)
 * @param    env                 Environment linked list address
 */
void		execute_command(t_cmd *cmd, t_env **env);

/**
 * @brief    Handle PATH browsing and path concatenation if found
 * 
 */

/**
 * @brief    Resolve a command based on PATH value.
 * 
 * @param    command_name        Command name
 * @param    path_value          PATH environement value
 * @return   char*               Command path (should be FREE), or NULL
 */
char		*resolve_path(char *command_name, char *path_value);

#endif
