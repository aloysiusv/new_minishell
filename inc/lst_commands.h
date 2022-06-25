/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:46:17 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 17:46:50 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_CMD_H
# define LST_CMD_H

# include "minishell.h"

typedef struct 			s_command
{
	char				**command;
	char				*full_line;
	char				*exec_path;
	char				*redir;
	int					fdin;
	int					fdout;
	struct s_command	*next;
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