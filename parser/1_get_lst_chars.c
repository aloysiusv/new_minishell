/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_get_lst_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:04:56 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/28 16:10:46 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_expansion_flags(t_node **head)
{
	t_node	*iterator;

	iterator = *head;
	while (iterator)
	{
		if (iterator->type == DOLLAR && iterator->next)
		{
			if (ft_isdigit(iterator->next->charac))
			{
				iterator->type = USELESS;
				iterator->next->type = USELESS;
				iterator = iterator->next;
			}
			else if (!ft_isset(iterator->next->charac, "~!@#$/\\%^&*()+- 	"))
				iterator->type = LITERAL;
			else
			{
				iterator = iterator->next;
				while (iterator->next && iterator->next->type == LITERAL)
				{
					iterator->type = DOLLAR;
					iterator = iterator->next;
				}
				iterator->type = DOLLAR;
			}
		}
		iterator = iterator->next;
	}
}

static void	set_literals(t_node **head)
{
	t_node	*iterator;

	iterator = *head;
	while (iterator)
	{
		if (iterator->in_squotes || iterator->in_dquotes)
		{
			if (iterator->type == USELESS)
				iterator->type = BLANK;
			else if (iterator->type == DOLLAR && iterator->in_dquotes)
				iterator->type = DOLLAR;
			else
				iterator->type = LITERAL;
		}
		if (iterator->next)
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
	if (iterator->next)
		*iterator = (*iterator)->next;
}

static void	set_subflags(t_node **head)
{
	t_node	*iterator;

	iterator = *head;
	while (iterator)
	{
		if (iterator->charac == '\'')
			set_quote_flags(&iterator, '\'');
		else if (iterator->charac == '\"')
			set_quote_flags(&iterator, '\"');
		iterator = iterator->next;
	}
	set_literals(head);
	set_expansion_flags(head);
}

static int	is_valid_input(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	get_lst_chars(char *cmdline, t_node **chars)
{
	if (is_valid_input(cmdline) == 0)
	{
		ft_putstr_fd("minishell: error: ", 2);
		ft_putstr_fd("'", 2);
		ft_putstr_fd(cmdline, 2);
		ft_putstr_fd("'", 2);
		ft_putstr_fd(" command not found", 2);
		g_exit_code = 2;
		return (-1);
	}
	*chars = chars_to_lst(cmdline, chars);
	set_subflags(chars);
	return (EXIT_SUCCESS);
	// t_node	*iterator = *char;
	// while (iterator)
    // {
    //     printf("[%c] => in_squotes [%d] || in_dquotes [%d] || type [%d]\n", iterator->charac,
	// 		iterator->in_squotes, iterator->in_dquotes, iterator->type);
	// 	iterator = iterator->next;
    // }
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
