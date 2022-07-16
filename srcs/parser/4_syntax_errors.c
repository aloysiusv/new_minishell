/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_syntax_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmachrou <wmachrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 03:17:55 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 18:58:51 by wmachrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_ope_args(t_node *head)
{
	t_node	*iterator;

	iterator = head;
	while (iterator)
	{
		if (iterator->type == RD_INPUT || iterator->type == RD_OUTPUT
			|| iterator->type == APPEND || iterator->type == HRDOC
			|| iterator->type == PIPE)
		{
			if (!iterator->next)
				return (-1);
			if (iterator)
				iterator = iterator->next;
			skip_blanks(&iterator);
			if (iterator && iterator->type != LITERAL)
				return (-1);
		}
		if (iterator)
			iterator = iterator->next;
	}
	return (0);
}

static int	is_it_valid(char *operator, char ope)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (operator[i])
	{
		if (operator[i] == ope)
			count++;
		i++;
	}
	if (count > 1)
		return (-1);
	return (0);
}

static void	error_print(char *s)
{
	printf("minishell: syntax error near unexpected token `%s'\n", s);
}

static int	check_valid_operators(t_node *head)
{
	t_node				*iterator;
	size_t				i;
	const t_operator	list[] = {{RD_INPUT, '<'}, {RD_OUTPUT, '>'},
	{PIPE, '|'}};

	iterator = head;
	while (iterator)
	{
		i = -1;
		while (++i < 3)
		{
			if (iterator->type == list[i].type)
			{
				if (is_it_valid(iterator->word, list[i].ope) == -1)
				{
					error_print(iterator->word);
					return (-1);
				}
			}
		}
		if (iterator)
			iterator = iterator->next;
	}
	return (0);
}

int	syntax_errors(t_node *tokens)
{
	if (!tokens)
		return (-1);
	if (check_valid_operators(tokens) == -1)
		return (-1);
	if (check_ope_args(tokens) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (-1);
	}
	return (0);
}
