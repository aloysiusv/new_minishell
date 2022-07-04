/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:09:02 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 03:15:51 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "../libft/libft.h"
# include "structs.h"

# define PROGRAM_NAME	"minishell"
# define PROMPT	"~=mini$hell=~> "
# define PROMPT_HEREDOC	"> "
# define ALL_SPACES " 	\x20\x08\x09\x0a\x0b\x0c\x0d"

/* Modes to specify when creating nodes */
# define FIRST		0
# define NEXT		1

extern unsigned short	g_exit;

/*=================================PARSING=================================== */

int			get_lst_chars(char *cmdline, t_node **chars);
void		get_lst_tokens(t_node *chars, t_node **tokens);
void		get_lst_expanded(t_node **tokens, t_env *vars);
size_t		get_tab_cmds(t_shell *sh);
int			set_chars_subflags(t_node **chars);
void		set_expansion_flags(t_node **chars);
void    	set_tokens_subflags(t_node **tokens);
void 		set_filename_flags(t_node **tokens);
void		set_filetype(t_node **tok, int mode, int ignore, int assign);
void		get_io_files(t_cmd *cmd);

int			syntax_errors(t_node *lst);
void		delete_lst(t_node **lst);
void		delete_cmds_tab(t_shell *sh);

/*=================================EXPANSION================================== */

void		expand_word(t_node **iterator, t_env *vars);

/*=================================ENV======================================== */
	
t_env		*create_lst_env(char **env);
char		**get_envp(char **env);
char		**convert_env(t_env *vars);
char		*find_env(t_env *vars, char *key);
void		update_env(t_env *vars, char *key, char *value);

/* utils_nodes_var.c */
t_env		*create_node(char *key, char *value);
void		push_back_node(t_env **head, t_env *node);
void		delete_node(t_env *node);
void		remove_node(t_env **head, char *key);
char		**split_var(char const *s);

void		delete_node_env(t_env *node);
void		delete_specific_node_env(t_env **head, char *key);
void		delete_lst_env(t_env **head);
t_env		*create_node_env(char **keyvalue);
t_env		*add_bottom_node_env(char **keyvalue, t_env *last);
t_env		*add_top_node_env(char **keyvalue, t_env *current_top);
void	    delete_fork(t_shell *sh, t_env **env, size_t status);

/*=================================EXEC======================================= */

int			launch_commands(t_shell *sh, t_env **env);
void		execute_command(t_shell *sh, size_t i, t_env **env);

int			handle_redirect(t_cmd *cmd, t_env **env);
int			redirect_command(int fdin, int fdout);
int			handle_infile(t_cmd *cmd, t_env **env, char *filename);
int			handle_limiter(t_cmd *cmd, t_env **env, char *filename);
int			handle_outfile(t_cmd *cmd, t_env **env, char *filename);
int			handle_outfile_a(t_cmd *cmd, t_env **env, char *filename);

char		*resolve_path(char *command_name, char *path_value);

/*=================================HRDOC====================================== */

int			heredoc(char *limiter, t_cmd *cmd, t_env **env);
int			hrdoc_get_lst_chars(char *line, t_node **chars);
void		hrdoc_get_lst_tokens(t_node *chars, t_node **tokens);
void		hrdoc_get_lst_expanded(t_node **tokens, t_env *vars);

/*=================================BUILT-INS================================== */

int			launch_builtin(t_cmd *cmd, t_env **env, t_builtinp builtin);
t_builtinp	is_builtin(t_cmd *cmd);

int			builtin_echo(t_cmd *cmd, t_env **env);
int			builtin_test(t_cmd *cmd, t_env **env);
int			builtin_cd(t_cmd *cmd, t_env **env);
int			builtin_pwd(t_cmd *cmd, t_env **env);
int			builtin_export(t_cmd *cmd, t_env **env);
int			builtin_unset(t_cmd *cmd, t_env **env);
int			builtin_env(t_cmd *cmd, t_env **env);
int			builtin_exit(t_cmd *cmd, t_env **env);

/*=================================NODES====================================== */

/* utils_nodes.c */
t_node		*t_node_create(char my_char, char *my_word, int my_type);
t_node		*t_node_addlast(t_node *last, char value, char *word, int type);
void		t_node_push(t_node **pushing, t_node **receiving);
void		t_node_push_new(t_node **tokens, t_node *new);
void		t_node_delete(t_node *node);
void		t_node_delete_lst(t_node **head);
void		t_node_delete_specific(t_node **head, t_node *to_delete);
void		t_node_delete_useless_tokens(t_node **tokens, int type);
void		skip_blanks(t_node **iterator);

/*=================================UTILS====================================== */

/* utils.c */
char		*lst_to_str(t_node *lst);
char		**lst_to_tab(t_node *lst);
size_t		get_nb_types(t_node *tokens, int type);
size_t		get_tab_size(char **tab);
size_t		ft_lstsize_2(t_node *head);

/* utils_errors.c */
int			p_error(char *error_message, int exit_code);
void		print_error(const char *file, const char *msg, const int errnum);

/* utils_free.c */
void		free_tab(char **tab);
void		free_prev(char **tab, size_t nb_words);
void		free_shell(t_shell *sh);

/*=================================MISC======================================= */

/* signals.c */
void		handle_signal(int sig);
/* Mixed functions */
void		get_expands(t_node **tokens, t_env *vars);

#endif
