/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_a_parse_lst_chars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:03:49 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/21 21:14:35 by lrandria         ###   ########.fr       */
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

static void	get_next_char(char *str, size_t *i, t_node **curr)	
{
	while (str[*i])
	{
		if (str[*i] == '\'')
			(*curr)->next = add_bottom_node(*curr, '\'', NULL, SQUOTE);
		else if (str[*i] == '\"')
			(*curr)->next = add_bottom_node(*curr, '\"',NULL,  DQUOTE);
		else if (str[*i] == '<')
			(*curr)->next = add_bottom_node(*curr, '<', NULL, RD_INPUT);
		else if (str[*i] == '>')
			(*curr)->next = add_bottom_node(*curr, '>', NULL, RD_OUTPUT);
		else if (str[*i] == '|')
			(*curr)->next = add_bottom_node(*curr, '|', NULL, PIPE);
		else if (str[*i] == '$')
			(*curr)->next = add_bottom_node(*curr, '$', NULL, DOLLAR);
		else if (str[*i] == '=')
			(*curr)->next = add_bottom_node(*curr, '=', NULL, EQUAL);
		else if (ft_isset(str[*i], WHITE_SPACES) == 1)
			(*curr)->next = add_bottom_node(*curr, ' ', NULL, BLANK);
		else
			(*curr)->next = add_bottom_node(*curr, str[*i], NULL, LITERAL);
		*curr = (*curr)->next;
		(*i)++;
	}
}

t_node *create_lst_chars(char *s, t_node **head)
{
	size_t	i;
	t_node	*curr;
	char	*str;

	if (!s || !*(head))
		return (NULL);
	str = trim_spaces(s);
	*head = get_first_char(str);
	curr = *head;
	i = 1;
	get_next_char(s, &i, &curr);	
	free(str);
	return (*head);
}
