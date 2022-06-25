/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_a_get_lst_chars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:04:56 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 08:05:45 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_literals(t_node **head)
{
	t_node	*iterator;

	iterator = *head;
	while (iterator)
	{
		if (iterator->in_squotes || iterator->in_dquotes)
		{
			if (iterator->type == DOLLAR && iterator->in_dquotes)
				iterator->type = DOLLAR;
			else
				iterator->type = LITERAL;
		}
		if (iterator)
			iterator = iterator->next;
	}
}

static void	set_quote_flags(t_node **iterator, char quote)
{
	*iterator = (*iterator)->next;
	while (*iterator && (*iterator)->charac != quote)
	{
		if (quote == '\'')
			(*iterator)->in_squotes = true;
		else if (quote == '\"')
			(*iterator)->in_dquotes = true;
		*iterator = (*iterator)->next;
	}
	if (*iterator)
		(*iterator) = (*iterator)->next;
}

void	set_subflags(t_node **head)
{
	t_node	*iterator;

	iterator = *head;
	while (iterator)
	{
		if (iterator->charac == '\'')
			set_quote_flags(&iterator, '\'');
		else if (iterator->charac == '\"')
			set_quote_flags(&iterator, '\"');
		if (iterator)
			iterator = iterator->next;
	}
	set_literals(head);
}

void	characters_to_lst(char *cmdline, t_node **src)
{
	t_node	*iterator;

    *src = cmdline_to_lst(cmdline, src);
	set_subflags(src);
    iterator = *src;
	while (iterator)
    {
        printf("[%c] => in_squotes [%d] || in_dquotes [%d]\n", iterator->charac, iterator->in_squotes, iterator->in_dquotes);
		iterator = iterator->next;
    }
}

// int main(void)
// {
// 	char	*cmdline = "  \"COOOL\" CO |'||'| \\ ? <<<' > ";
// 	t_node  iterator;
// 	t_node	*src;

// 	src = NULL;
// 	characters_to_lst(cmdline, &src, &iterator);
// 	delete_lst(&src);
// 	return (0);
// }