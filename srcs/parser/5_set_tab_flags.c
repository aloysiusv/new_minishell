/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_set_tab_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmachrou <wmachrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:40:03 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 10:41:17 by wmachrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	how_many_redirs(t_node *tokens)
{
	size_t	redirs;

	redirs = get_nb_types(tokens, INFILE);
	redirs += get_nb_types(tokens, LIMITER);
	redirs += get_nb_types(tokens, OUTFILE);
	redirs += get_nb_types(tokens, OUTFILE_A);
	return (redirs);
}

void	get_io_files(t_cmd *cmd)
{
	size_t	i;
	t_node	*iterator;

	cmd->nb_files = how_many_redirs(cmd->tokens);
	cmd->files = ft_calloc(cmd->nb_files, sizeof(t_file));
	if (!cmd)
		return ;
	i = 0;
	iterator = cmd->tokens;
	while (iterator)
	{
		if (iterator->type == INFILE || iterator->type == LIMITER
			|| iterator->type == OUTFILE || iterator->type == OUTFILE_A)
		{
			cmd->files[i].name = ft_strdup(iterator->word);
			cmd->files[i].type = iterator->type;
			if (iterator->in_squotes)
				cmd->files[i].quote = true;
			else if (iterator->in_dquotes)
				cmd->files[i].quote = true;
			i++;
		}
		iterator = iterator->next;
	}
}

void	set_filename_flags(t_node **tokens)
{
	t_node	*iterator;

	iterator = *tokens;
	while (iterator)
	{
		if (iterator->type == BLANK
			&& (iterator->in_squotes || iterator->in_dquotes))
			iterator->type = LITERAL;
		else if (iterator->type == INFILE || iterator->type == LIMITER
			|| iterator->type == OUTFILE || iterator->type == OUTFILE_A
			|| iterator->type == RD_INPUT || iterator->type == RD_OUTPUT
			|| iterator->type == APPEND || iterator->type == HRDOC)
			iterator->type = FILENAME;
		if (iterator)
			iterator = iterator->next;
	}
}

void	set_filetype(t_node **tok, int mode, int ignore, int assign)
{
	t_node	*iterator;

	if (!*tok)
		return ;
	iterator = *tok;
	while (iterator && iterator->next)
	{
		if (iterator->type == mode)
		{
			iterator = iterator->next;
			while (iterator && iterator->type == ignore)
				iterator = iterator->next;
			iterator->type = assign;
		}
		if (iterator)
			iterator = iterator->next;
	}
}
