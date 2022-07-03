/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:39:00 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 17:48:19 by lrandria         ###   ########.fr       */
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
# include "structs.h"
# include "exec.h"

// # define PROMPT "\x1b[1;35m~mini$hell~>\x1b[m "
# define PROMPT "~==mini$hell==~> "

/* Modes to specify when creating nodes */
# define FIRST		0
# define NEXT		1

/* Modes to specify when creating lst */
# define NOT_IN_HRDOC	0
# define IN_HRDOC		1

# define ALL_SPACES " 	\x20\x08\x09\x0a\x0b\x0c\x0d"

extern int	g_exit_code;

/*=================================PARSING=================================== */

int	get_lst_chars(char *cmdline, t_node **chars);
void	get_lst_tokens(t_node *chars, t_node **tokens);
void	get_lst_expanded(t_node **tokens, t_env *vars);
int	set_chars_subflags(t_node **chars);
void	set_expansion_flags(t_node **head);
void    set_tokens_subflags(t_node **tokens);
void	get_tab_cmds(t_cmd **cmds, t_node **tokens);
void	get_io_files(t_cmd *cmd);
void 	set_filename_flags(t_node **tokens);
void	set_filetype(t_node **tok, int mode, int ignore, int assign);
int	syntax_errors(t_node *tokens);
void	delete_cmds_tab(t_cmd **cmds);

/*=================================EXPANSION================================== */

void	expand_word(t_node **iterator, t_env *vars);

/*=================================ENV======================================== */
	
t_env	*create_lst_env(char **env);
char	**get_envp(char **env);

/*=================================EXEC======================================= */

void	exec_builtin(t_cmd *c, t_shell *sh);
void	exec_hrdoc(t_cmd *c, t_shell *sh);

/*=================================HRDOC====================================== */

void	hrdoc_get_lst_expanded(t_node **tokens, t_env *vars);
void	hrdoc_get_lst_tokens(t_node *chars, t_node **tokens);
int		hrdoc_get_lst_chars(char *line, t_node **chars);

/*=================================BUILT-INS================================== */

void	ft_echo(t_cmd *c);

/*=================================NODES====================================== */

/* utils_nodes.c */
t_node		*get_lst_tail(t_node *head);
void		delete_node(t_node *node);
void		delete_specific_node(t_node **head, t_node *to_delete);
void		delete_lst(t_node **head);
t_node		*create_node(char my_char, char *my_word, int my_type);
t_node		*add_bottom_node(t_node *last, char value, char *word, int type);
void		push(t_node **pushing, t_node **receiving);
void	skip_blanks(t_node **iterator);
void	push_back(t_node **tokens, t_node *new);

/* utils_nodes_var.c */
void		delete_node_env(t_env *node);
void		delete_specific_node_env(t_env **head, char *key);
void		delete_lst_env(t_env **head);
t_env		*create_node_env(char **keyvalue);
t_env		*add_bottom_node_env(char **keyvalue, t_env *last);
t_env		*add_top_node_env(char **keyvalue, t_env *current_top);

/*=================================UTILS====================================== */

/* utils.c */
char	*lst_to_str(t_node *lst);
char	**lst_to_tab(t_node *lst);
void	delete_useless_tokens(t_node **tokens, int type);
size_t	get_nb_types(t_node *tokens, int type);
size_t	get_tab_size(char **tab);
size_t		ft_lstsize_2(t_node *head);

/* utils_errors.c */
void	oops_crash(t_shell *shell, char *error_message, int exit_code);
int		print_error(char *error_message, int exit_code);
/* utils_free.c */
void	free_tab(char **tab);
void	free_prev(char **tab, size_t nb_words);
void	free_shell(t_shell *sh);

/*=================================MISC======================================= */

/* signals.c */
void	handle_signal(int sig);
/* Mixed functions */
void	get_expands(t_node **tokens, t_env *vars);

#endif
