/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:00:50 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 07:27:46 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct 			s_command
{
	char				**command;
	char				*cmd_path;
	int					fdin;
	int					fdout;
	int					redir;
	struct 	s_command	*next;
}						t_command;

typedef struct s_hdoc
{
	int		fdin;
	int		fdout;
	int		fds[2];
	char	*limiter;
	char	*line;
}				t_hdoc;
#endif