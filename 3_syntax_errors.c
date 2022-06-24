/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_syntax_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 03:17:55 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 07:28:57 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int		check_redirs_args(t_node *head)
// {
// 	t_node	*iterator;

// 	iterator = head;
// 	while (iterator)
// 	{
// 		if (iterator->type == RD_INPUT || iterator->type == RD_OUTPUT
// 			|| iterator->type == APPEND || iterator->type == HRDOC)
// 			if (!iterator->next || iterator->next->type != LITERAL)
// 				return (printf("error: invalid token `%s'\n", iterator->next->word), -1);
// 		iterator = iterator->next;
// 	}
// 	return (0);
// }

// static int		assign_word_types(t_node **head)
// {
// 	t_node	*iterator;

// 	iterator = *head;
// 	while (iterator)
// 	{
// 		if (iterator->type == LITERAL)
// 		{
// 			if (iterator->prev && (iterator->prev->type == RD_INPUT
// 				|| iterator->prev->type == RD_OUTPUT
// 				|| iterator->prev->type == APPEND))
// 				iterator->type = FILENAME;
// 			else if (iterator->prev && iterator->prev->type == HRDOC)
// 				iterator->type = LIMITER;
// 		}
// 	}
// 	return (0);
// }

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
		{DOLLAR, '$'},
		{EQUAL, '='}
	};

    iterator = head;
    while (iterator)
    {
		i = -1;
		while (++i < 5)
			if (iterator->type == list[i].type)
				if (is_it_valid(iterator->word, list[i].ope) == -1)
					return (printf("minishell: error: syntax error near operator `%c'\n",
						list[i].ope), -1);
        iterator = iterator->next;
    }
	return (0);
}

static int		check_closing_quotes(t_node *head)
{
	t_node  *iterator;

	iterator = head;
	while (iterator->next)
		iterator = iterator->next;
	if (iterator->in_squotes || iterator->in_dquotes)
		return (-1);
	return (0);
}

int	syntax_errors(t_node *tokens)
{
	if (check_closing_quotes(tokens) == -1)
		return (printf("minishell: error: unclosed quotes\n"), -1);
	if (check_valid_operators(tokens) == -1)
		return (-1);
	return (0);
}

// int main(void)
// {
// 	char	*cmdline = "  \"COOOL\" CO | '||' \\ ? > ";
// 	t_node	*src;
// 	t_node	*dest;

// 	src = NULL;
// 	dest = NULL;
// 	characters_to_lst(cmdline, &src);
// 	printf("==================================================================\n");
// 	words_to_lst(src, &dest);
// 	if (check_closing_quotes(dest) == -1)
// 		return (printf("minishell: error: unclosed quotes\n"), -1);
// 	if (check_valid_operators(dest) == -1)
// 		return (-1);
// 	//do expansions (convert dollars)
// 	if (assign_word_types(&dest) == -1)
// 		return (-1);
// 	if (check_redirs_args(dest) == -1)
// 		return (-1);
// 	delete_lst(&src);
// 	delete_lst(&dest);
// 	return (0);
// }
