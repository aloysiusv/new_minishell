/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_expansions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:18:30 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 07:45:37 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_expansions(t_node **tokens)
{
	t_node	*iterator;

	iterator = *tokens;
	while (iterator)
	{
		if (iterator->type == DOLLAR)
		{
			printf("work in progress\n");
			printf("to expand [$%s]\n", iterator->next->word);
		}
		iterator = iterator->next;
	}
}

int main(void)
{
	char	*cmdline = "  \"COOOL\" CO |>>>\"$USER\" '||' \\ ? > ";
	t_node	*src;
	t_node	*dest;

	src = NULL;
	dest = NULL;
	characters_to_lst(cmdline, &src);
	printf("==================================================================\n");
	words_to_lst(src, &dest);
	syntax_errors(dest);
	handle_expansions(&dest);
	delete_lst(&src);
	delete_lst(&dest);
	return (0);
}
