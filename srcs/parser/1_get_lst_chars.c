/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_get_lst_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:35:41 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 20:52:01 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_next_char(char *str, size_t *i, t_node **curr)
{
	if (str[*i] == '\'')
		(*curr)->next = t_node_addlast(*curr, '\'', NULL, SQUOTE);
	else if (str[*i] == '\"')
		(*curr)->next = t_node_addlast(*curr, '\"',NULL,  DQUOTE);
	else if (str[*i] == '<')
		(*curr)->next = t_node_addlast(*curr, '<', NULL, RD_INPUT);
	else if (str[*i] == '>')
		(*curr)->next = t_node_addlast(*curr, '>', NULL, RD_OUTPUT);
	else if (str[*i] == '|')
		(*curr)->next = t_node_addlast(*curr, '|', NULL, PIPE);
	else if (str[*i] == '$')
		(*curr)->next = t_node_addlast(*curr, '$', NULL, DOLLAR);
	else if (ft_isset(str[*i], ALL_SPACES) == 1)
		(*curr)->next = t_node_addlast(*curr, ' ', NULL, BLANK);
	else
		(*curr)->next = t_node_addlast(*curr, str[*i], NULL, LITERAL);
}

static t_node	*get_first_char(char *str)
{
	if (str[0] == '\'')
		return(t_node_create('\'', NULL, SQUOTE));
	else if (str[0] == '\"')
		return(t_node_create('\"', NULL, DQUOTE));
	else if (str[0] == '<')
		return(t_node_create('<', NULL, RD_INPUT));
	else if (str[0] == '>')
		return(t_node_create('>', NULL, RD_OUTPUT));
	else if (str[0] == '|')
		return(t_node_create('|', NULL, PIPE));
	else if (str[0] == '$')
		return(t_node_create('$', NULL, DOLLAR));
	else if (ft_isset(str[0], ALL_SPACES) == 1)
		return(t_node_create(' ', NULL, BLANK));
	else
		return(t_node_create(str[0], NULL, LITERAL));
}

static char	*trim_spaces(char const *str)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] && ft_isset(str[i], ALL_SPACES) == 1)
		i++;
	j = ft_strlen(str) - 1;
	while (ft_isset(str[j], ALL_SPACES) == 1)
		j--;
	new_s = ft_substr(str, i, j + 1 - i);
	return (new_s);
}

int	get_lst_chars(char *line, t_node **chars)
{
	size_t	i;
	t_node	*curr;
	char	*str;

	if (!line || !*line)
		return (-1);
	str = trim_spaces(line);
	*chars = get_first_char(str);
	curr = *chars;
	i = 1;
	while (str[i])
	{
		get_next_char(str, &i, &curr);
		if (!curr)
			return (-1);
		curr = curr->next;
		i++;
	}
	free(str);
	if (set_chars_subflags(chars) == -1)
		return (-1);
	return (0);
}
