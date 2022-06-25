/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tokens.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 05:56:12 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 17:49:57 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_TOKENS_H
# define LST_TOKENS_H

# include "minishell.h"

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

/* 1_a_get_lst_chars */
t_node 	*cmdline_to_lst(char *line, t_node **head);
/* 1_b_get_lst_chars.c */
void	characters_to_lst(char *cmdline, t_node **src);
/* 2_get_lst_tokens.c */
void	words_to_lst(t_node *src, t_node **dest);
/* 3_syntax_errors.c */
int	syntax_errors(t_node *tokens);
/* 4_expansions */
void	handle_expands(t_node **tokens);

/* utils_nodes.c */
size_t	ft_lstsize_2(t_node *head);
void	delete_node(t_node *node);
void	delete_lst(t_node **head);
t_node	*create_node(char my_char, char *my_word, int my_type);
t_node	*add_bottom_node(t_node *current_last, char value, char *word, int type);
#endif