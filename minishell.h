/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:39:00 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/20 23:34:39 by lrandria         ###   ########.fr       */
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

# define WHITE_SPACES " 	\0\n\t\v\f\r"

# define FIRST_WORD		0
# define NEXT_WORD		1

enum e_type
{
	LITERAL,
	WORD,
	BUILTIN,
	FILENAME,
	COMMAND,
	LIMITER,
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

typedef struct		s_lst
{
	size_t	size;
	t_node	*head;
	t_node	*tail;
}					t_lst;

typedef struct		s_shell
{
	char	*cmdline;
	char	**envp;
	size_t	nb_cmds;
	size_t	nb_redir;
}					t_shell;

/* utils_libft.c */
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isset(char c, char const *my_set);
size_t	ft_strlcpy(char *dst, const	char *src, size_t size);
size_t	ft_strlen(const char *s);

/* utils_nodes.c */
size_t	ft_lstsize(t_lst *lst);
void	delete_node(t_node *node);
void	delete_lst(t_lst *lst);
t_node	*create_node(char my_char, char *my_word, int my_type);
t_node	*add_bottom_node(t_node *current_last, char value, char *word, int type);

/* 0_cmdline_to_lst.c */
t_node	*init_first_node(char *str);
t_node	*cmdline_to_lst(char *str, t_node **head);

#endif
