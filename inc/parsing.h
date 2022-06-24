/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 05:56:12 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 08:10:10 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/* Modes to specify when creating word nodes */
# define FIRST_WORD		0
# define NEXT_WORD		1

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

#endif