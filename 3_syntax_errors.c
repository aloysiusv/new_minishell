/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_syntax_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 03:17:55 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 04:39:37 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_it_valid(char *operator, char ope)
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

int     check_valid_operators(t_node *head)
{
    t_node  *iterator;

    iterator = head;
    while (iterator)
    {
        if (iterator->type == RD_INPUT)
        {
			if (is_it_valid(iterator->word, '<') == -1)
				return (printf("error: syntax error near operator `%c'\n", '<')-1);
		}
		else if (iterator->type == RD_OUTPUT)
        {
			if (is_it_valid(iterator->word, '>') == -1)
				return (printf("error: syntax error near operator `%c'\n", '>')-1);
		}
        else if (iterator->type == PIPE)
        {
			if (is_it_valid(iterator->word, '|') == -1)
				return (printf("error: syntax error near operator `%c'\n", '|')-1);
		}
        else if (iterator->type == DOLLAR)
        {
			if (is_it_valid(iterator->word, '$') == -1)
				return (printf("error: syntax error near operator `%c'\n", '$')-1);
		}
        else if (iterator->type == EQUAL)
        {
			if (is_it_valid(iterator->word, '=') == -1)
				return (printf("error: syntax error near operator `%c'\n", '=')-1);
		}
        iterator = iterator->next;
    }
	return (0);
}

int		check_closing_quotes(t_node *head)
{
	t_node  *iterator;

	iterator = head;
	while (iterator->next)
		iterator = iterator->next;
	if (iterator->in_squotes || iterator->in_dquotes)
		return (-1);
	return (0);
}

int main(void)
{
	char	*cmdline = "  \"COOOL\" CO ||  '||' \\ ? <> ";
	t_node	*src;
	t_node	*dest;

	src = NULL;
	dest = NULL;
	characters_to_lst(cmdline, &src);
	printf("==================================================================\n");
	words_to_lst(src, &dest);
	if (check_closing_quotes(dest) == -1)
		return (printf("error: unclosed quotes\n"), -1);
	if (check_valid_operators(dest) == -1)
		return (printf("error: invalid operators\n"), -1);
	delete_lst(&src);
	delete_lst(&dest);
	return (0);
}
