/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_set_tokens_subflags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:40:34 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/29 20:26:20 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    set_input_filetype(t_node **tokens)
{
    t_node	*iterator;

	iterator = *tokens;
	while (iterator && iterator->next)
	{
		if (iterator->type == RD_INPUT)
		{
			iterator = iterator->next;
			while (iterator && iterator->type == BLANK)
				iterator = iterator->next;
            iterator->type = INFILE;
		}
	    else if (iterator->type == HRDOC && iterator->next)
		{
			iterator = iterator->next;
			while (iterator && iterator->type == BLANK)
				iterator = iterator->next;
            iterator->type = LIMITER;
		}
        iterator = iterator->next;
    }
}

static void    set_output_filetype(t_node **tokens)
{
    t_node	*iterator;

	iterator = *tokens;
	while (iterator && iterator->next)
	{
        if (iterator->type == RD_OUTPUT && iterator->next)
		{
			iterator = iterator->next;
			while (iterator->type == BLANK)
				iterator = iterator->next;
			iterator->type = OUTFILE;
		}
		else if (iterator->type == APPEND && iterator->next)
		{
			iterator = iterator->next;
			while (iterator->type == BLANK)
				iterator = iterator->next;
			iterator->type = OUTFILE_A;
		}
		iterator = iterator->next;
	}
}

// static void    set_cmd_type(t_node **tokens)
// {
//     t_node	*iterator;

// 	iterator = *tokens;
// 	while (iterator && iterator->next)
// 	{
//         if (iterator->type == PIPE && iterator->next)
//         {
// 		    iterator = iterator->next;
// 			while (iterator && iterator->type == BLANK)
// 				iterator = iterator->next;
// 			iterator->type = CMD;
//         }
// 		iterator = iterator->next;
// 	}
// }

// static void    set_arg_type(t_node **tokens)
// {
//     t_node	*iterator;

// 	iterator = *tokens;
// 	while (iterator && iterator->next)
// 	{
//         if ((iterator->type == CMD || iterator->type == ARGS)
// 			&& iterator->next)
// 		{
// 			iterator = iterator->next;
// 			while (iterator && iterator->type == BLANK)
// 				iterator = iterator->next;
// 			iterator->type = ARGS;
// 		}
// 		iterator = iterator->next;
// 	}
// }

void    set_tokens_subflags(t_node **tokens)
{
    if (!tokens)
		return ;
	set_input_filetype(tokens);
    set_output_filetype(tokens);
    // set_cmd_type(tokens);
    // set_arg_type(tokens);
}
