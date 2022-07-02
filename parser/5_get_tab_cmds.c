/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_get_tab_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:39:48 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 16:12:27 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_files_tab(t_file *files, size_t nb_files)
{
	size_t	i;

	i = 0;
	while (i < nb_files)
	{
		// if (files[i].name)
		printf("file[%zu] => [%s][%d]\n", i, files[i].name, files[i].type);
		i++;
	}
}

static void	print_cmds_tab(t_cmd *cmds)
{
	size_t	i;

	if (!cmds)
		return ;
	i = 0;
	while (i < cmds->nb_cmds)
	{
		printf("CMD[%s] =>\n", cmds[i].command[0]);
		print_files_tab(cmds[i].files, cmds[i].nb_files);
		i++;
	}
}

static void	print_str_tab(char **str)
{
	size_t	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		printf("[%s]\n", str[i]);
		i++;
	}
}

static void	join_literals(t_node **tokens)
{
	t_node	*iterator;
	char	*copy;

	if (!*tokens)
		return ;
	iterator = *tokens;
	while (iterator)
	{
		if (iterator->type == LITERAL
			&& iterator->next && iterator->next->type == LITERAL)
		{
			copy = ft_strdup(iterator->next->word);
			free(iterator->next->word);
			iterator->next->word = ft_strjoin(iterator->word, copy);
			iterator->type = USELESS;
			free(iterator->word);
			free(copy);
			iterator->word = NULL;
		}
		else if (iterator->type == BLANK)
			iterator->type = USELESS;
		if (iterator)
			iterator = iterator->next;	
	}
}

static void	set_filename_flags(t_node **tokens)
{
    t_node	*iterator;

	iterator = *tokens;
	while (iterator)
	{
		if (iterator->type == BLANK && (iterator->in_squotes || iterator->in_dquotes))
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

static size_t	how_many_redirs(t_node *tokens)
{
	size_t	redirs;

	redirs = get_nb_types(tokens, INFILE);
	redirs += get_nb_types(tokens, LIMITER);
	redirs += get_nb_types(tokens, OUTFILE);
	redirs += get_nb_types(tokens, OUTFILE_A);
	return (redirs);
}

static void	get_io_files(t_cmd *cmd)
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
			i++;
		}
		if (iterator)
			iterator = iterator->next;
	}
}

static void	set_filetype(t_node **tok, int mode, int ignore, int assign)
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

static void	push_back(t_node **tokens, t_node *new)
{
	t_node	*new_token;

	if (!tokens || !new)
		return ;
	if (*tokens == NULL)
	{
		*tokens = new;
		return ;
	}
	new_token = *tokens;
	while (new_token->next)
		new_token = new_token->next;
	new_token->next = new;
}

void	get_tab_cmds(t_cmd **cmds, t_node **tokens)
{
	t_node	*iterator;
	t_node	*new;
	size_t	nb_cmds;
	size_t	i;

	nb_cmds = get_nb_types(*tokens, PIPE) + 1;
	*cmds = ft_calloc(nb_cmds, sizeof(t_cmd) + 1);
	if (!*cmds)
		return ;
	i = 0;
	iterator = *tokens;
	while (i < nb_cmds)
	{
		(*cmds)[i].index = i;
		(*cmds)[i].nb_cmds = nb_cmds;
		while (iterator && iterator->type != PIPE)
		{
			new = create_node(0, ft_strdup(iterator->word), iterator->type);
			push_back(&(*cmds)[i].tokens, new);
			if (iterator->in_squotes)
				new->in_squotes = true;
			else if (iterator->in_dquotes)
				new->in_dquotes = true;
			if (iterator)
				iterator = iterator->next;
		}
		join_literals(&(*cmds)[i].tokens);
		delete_useless_tokens(&(*cmds)[i].tokens, USELESS);
		set_filetype(&(*cmds)[i].tokens, RD_INPUT, BLANK, INFILE);
		set_filetype(&(*cmds)[i].tokens, RD_OUTPUT, BLANK, OUTFILE);
		set_filetype(&(*cmds)[i].tokens, HRDOC, BLANK, LIMITER);
		set_filetype(&(*cmds)[i].tokens, APPEND, BLANK, OUTFILE_A);
		get_io_files(&(*cmds)[i]);
		set_filename_flags(&(*cmds)[i].tokens);
		delete_useless_tokens(&(*cmds)[i].tokens, FILENAME);
		(*cmds)[i].command = lst_to_tab((*cmds)[i].tokens);
		printf("Char ** of cmd[%zu]\n", i);
		print_str_tab((*cmds)[i].command);
		printf("Command is [%s]\n", (*cmds)[i].command[0]);
		if (iterator && iterator->type == PIPE)
			iterator = iterator->next;
		i++;
	print_cmds_tab(*cmds);
	}
	// t_node *iteratoor = *tokens;
	// 	while (iteratoor)
	// 	{
	// 	printf("[%s]	=> in_squotes [%d] || in_dquotes [%d] || type [%d]\n",
	// 		iteratoor->word, iteratoor->in_squotes,
	// 			iteratoor->in_dquotes, iteratoor->type);
	// 	iteratoor = iteratoor->next;
	// }
}
