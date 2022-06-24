/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:39:00 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 06:59:29 by lrandria         ###   ########.fr       */
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
# include "execution.h"
# include "parsing.h"

# define WHITE_SPACES " 	\n\t\v\f\r"

extern int	g_exit_code;

typedef struct		s_shell
{
	char			*cmdline;
	char			**envp;
	size_t			nb_cmds;
	size_t			nb_redir;
	t_node			*env_var;
}					t_shell;

/* utils_extra_libft.c */
int		ft_isset(char c, char const *my_set);

/* utils_nodes.c */
size_t	ft_lstsize_2(t_node *head);
void	delete_node(t_node *node);
void	delete_lst(t_node **head);
t_node	*create_node(char my_char, char *my_word, int my_type);
t_node	*add_bottom_node(t_node *current_last, char value, char *word, int type);

#endif
