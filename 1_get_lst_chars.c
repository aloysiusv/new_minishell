/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_get_lst_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:43:26 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 07:27:02 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*trim_spaces(char const *str)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && ft_isset(str[i], WHITE_SPACES) == 1)
		i++;
	j = ft_strlen(str) - 1;
	while (ft_isset(str[j], WHITE_SPACES) == 1)
		j--;
	new_s = ft_substr(str, i, j + 1 - i);
	return (new_s);
}

static t_node	*get_first_char(char *str)
{
	if (str[0] == '\'')
		return(create_node('\'', NULL, SQUOTE));
	else if (str[0] == '\"')
		return(create_node('\"', NULL, DQUOTE));
	else if (str[0] == '<')
		return(create_node('<', NULL, RD_INPUT));
	else if (str[0] == '>')
		return(create_node('>', NULL, RD_OUTPUT));
	else if (str[0] == '|')
		return(create_node('|', NULL, PIPE));
	else if (str[0] == '$')
		return(create_node('$', NULL, DOLLAR));
	else if (str[0] == '=')
		return(create_node('=', NULL, EQUAL));
	else
		return(create_node(str[0], NULL, LITERAL));
}

t_node *cmdline_to_lst(char *line, t_node **head)
{
	size_t	i;
	t_node	*curr;
	char	*str;

	if (!line)
		return (NULL);
	str = trim_spaces(line);
	*head = get_first_char(str);
	curr = *head;
	i = 1;
	while (str[i])
	{
		if (str[i] == '\'')
			curr->next = add_bottom_node(curr, '\'', NULL, SQUOTE);
		else if (str[i] == '\"')
			curr->next = add_bottom_node(curr, '\"',NULL,  DQUOTE);
		else if (str[i] == '<')
			curr->next = add_bottom_node(curr, '<', NULL, RD_INPUT);
		else if (str[i] == '>')
			curr->next = add_bottom_node(curr, '>', NULL, RD_OUTPUT);
		else if (str[i] == '|')
			curr->next = add_bottom_node(curr, '|', NULL, PIPE);
		else if (str[i] == '$')
			curr->next = add_bottom_node(curr, '$', NULL, DOLLAR);
		else if (str[i] == '=')
			curr->next = add_bottom_node(curr, '=', NULL, EQUAL);
		else if (ft_isset(str[i], WHITE_SPACES) == 1)
			curr->next = add_bottom_node(curr, ' ', NULL, BLANK);
		else
			curr->next = add_bottom_node(curr, str[i], NULL, LITERAL);
		curr = curr->next;
		i++;
	}
	free(str);
	return (*head);
}

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