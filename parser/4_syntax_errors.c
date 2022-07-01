/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_syntax_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 03:17:55 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/01 04:35:08 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_blanks(t_node **iterator)
{
	while (*iterator && (*iterator)->type == BLANK)
		*iterator = (*iterator)->next;
}

static int		check_ope_args(t_node *head)
{
	t_node	*iterator;

	iterator = head;
	while (iterator)
	{
		if (iterator->type == RD_INPUT || iterator->type == RD_OUTPUT
			|| iterator->type == APPEND || iterator->type == HRDOC
			|| )
		{
			if (!iterator->next)
				return (-1);
			skip_blanks(&iterator);
			if (!iterator->next || iterator->next->type != LITERAL)
				return (-1);
		}
		iterator = iterator->next;
	}
	return (0);
}


static int		is_it_valid(char *operator, char ope)
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

static int     check_valid_operators(t_node *head)
{
    t_node  *iterator;
	size_t	i;
	const t_operator list[] = {
  		{RD_INPUT, '<'},
		{RD_OUTPUT, '>'},
		{PIPE, '|'},
	};

    iterator = head;
    while (iterator)
    {
		i = -1;
		while (++i < 3)
			if (iterator->type == list[i].type)
				if (is_it_valid(iterator->word, list[i].ope) == -1)
				{
					printf("minishell: error: syntax error near unexpected token `%s'\n", iterator->word);
					return (-1);
				}
        iterator = iterator->next;
    }

	return (0);
}

static int	check_closing_quotes(t_node *head)
{
	t_node  *iterator;

	if (!head)
		return (-1);
	iterator = head;
	while (iterator->next)
		iterator = iterator->next;
	if (iterator->in_squotes || iterator->in_dquotes)
		return (-1);
	return (0);
}

int	syntax_errors(t_node *tokens)
{
	if (!tokens)
		return (-1);
	if (check_closing_quotes(tokens) == -1)
	{
		print_error("unclosed quotes\n", 2);
		return (-1);
	}
	if (check_valid_operators(tokens) == -1)
		return (-1);
	if (check_ope_args(tokens) == -1)
	{
		print_error("syntax error near unexpected token `newline'\n", 2);
		return (-1);
	}
	return (0);
}

// int main(void)
// {
// 	char	*cmdline = "  \"COOOL\" CO | '||' \\ ? > ";
// 	t_shell	*sh;
// 	t_node	*src;
// 	t_node	*dest;

// 	src = NULL;
// 	dest = NULL;
// 	characters_to_lst(cmdline, &src);
// 	printf("==================================================================\n");
// 	words_to_lst(src, &dest);
// 	check_closing_quotes(dest);
// 	check_valid_operators(dest);
//	// do expansions (convert dollars)
// 	// if (assign_word_types(&dest) == -1)
// 	// 	return (-1);
// 	// if (check_redirs_args(dest) == -1)
// 	// 	return (-1);
// 	delete_lst(&src);
// 	delete_lst(&dest);
// 	return (0);
// }
