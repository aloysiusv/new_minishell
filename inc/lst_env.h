/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:44:14 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/25 04:44:31 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_ENV_H
# define LST_ENV_H

# include "minishell.h"

typedef struct		s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*prev;
	struct s_env_var	*next;
}                   t_env_var;

/* create_env.c */
t_env_var		*create_env_lst(char **env, t_env_var **head);

/* utils_nodes_var.c */
void		delete_node_var(t_env_var *node);
void		delete_specific_node_var(t_env_var **head, char *key);
void		delete_lst_var(t_env_var **head);
t_env_var	*create_node_var(char **keyvalue);
t_env_var	*add_bottom_node_var(char **keyvalue, t_env_var *current_last);
t_env_var	*add_top_node_var(char **keyvalue, t_env_var *current_top);

#endif