/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:39:00 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/26 02:42:57 by lrandria         ###   ########.fr       */
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

# define PROMPT "\x1b[1;35m~mini$hell~>\x1b[m "

/* Modes to specify when creating nodes */
# define FIRST		0
# define NEXT		1

# define WHITE_SPACES "     \x20\x08\x09\x0a\x0b\x0c\x0d"

extern int	g_exit_code;

/* create_env.c */
t_env		*create_lst_env(char **env);
/* utils_nodes_var.c */
void		delete_node_var(t_env *node);
void		delete_specific_node_var(t_env **head, char *key);
void		delete_lst_var(t_env **head);
t_env		*create_node_var(char **keyvalue);
t_env		*add_bottom_node_var(char **keyvalue, t_env *current_last);
t_env		*add_top_node_var(char **keyvalue, t_env *current_top);

/* 1_get_lst_chars */
void	get_lst_chars(char *cmdline, t_node **src);
/* 1_get_lst_chars2.c */
t_node *chars_to_lst(char *line, t_node **head);
/* 2_get_lst_tokens.c */
void	get_lst_tokens(t_node *src, t_node **dest);
/* utils_nodes.c */
size_t	ft_lstsize_2(t_node *head);
void	delete_node(t_node *node);
void	delete_specific_node(t_node **head, int type);
void	delete_lst(t_node **head);
t_node	*create_node(char my_char, char *my_word, int my_type);
t_node	*add_bottom_node(t_node *current_last, char value, char *word, int type);

/* utils_signals.c */
void	handle_signals(int sig);

/* Mixed functions */
void	syntax_errors(t_shell *sh, t_node *tokens);
void	get_expands(t_node **tokens, t_env *vars);

/* utils_errors.c */
void	oops_crash(t_shell *shell, char *error_message, int exit_code);

/* signals.c */
void	handle_signals(int sig);

/* utils_free.c */
void	free_tab(char **tab);
void	free_shell(t_shell *sh);

#endif
