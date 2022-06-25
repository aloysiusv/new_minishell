/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:44:14 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/25 10:26:29 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_ENV_H
# define LST_ENV_H

# include "minishell.h"

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}                   t_env;

/* create_env.c */
t_env		*create_env_lst(char **env, t_env **head);

/* utils_nodes_var.c */
void		delete_node_var(t_env *node);
void		delete_specific_node_var(t_env **head, char *key);
void		delete_lst_var(t_env **head);
t_env	*create_node_var(char **keyvalue);
t_env	*add_bottom_node_var(char **keyvalue, t_env *current_last);
t_env	*add_top_node_var(char **keyvalue, t_env *current_top);

#endif