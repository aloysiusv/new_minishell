/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:35:17 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 19:18:47 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_export(char *var)
{
	char	*p1;
	char	*p2;
	char	*error;

	p1 = ": export: `";
	p2 = "': not a valid identifier";
	error = ft_strsjoin((char *[]){PROGRAM_NAME, p1, var, p2, "\n", NULL}, "");
	if (error == NULL)
		return ;
	write(2, error, ft_strlen(error));
	free(error);
}

static int	invalid_export(char *var, int *status)
{
	size_t	i;

	if (!*var || (*var != '_' && !ft_isalpha(*var)))
	{
		error_export(var);
		*status = 1;
		return (1);
	}
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
		{
			error_export(var);
			*status = 1;
			return (1);
		}
		i++;
	}
	if (var[i] != '=')
		return (1);
	return (0);
}

int	handle_export(char **keyvalue, t_env **env)
{
	t_env	*node;

	if (find_env(*env, keyvalue[0]))
	{
		update_env(*env, keyvalue[0], keyvalue[1]);
		free(keyvalue[0]);
	}
	else
	{
		node = create_node(keyvalue[0], keyvalue[1]);
		if (node == NULL)
		{
			ft_free_strs(keyvalue);
			return (1);
		}
		push_back_node(env, node);
	}
	return (0);
}

int	builtin_export(t_cmd *cmd, t_env **env)
{
	char	**keyvalue;
	size_t	i;
	int		status;

	status = 0;
	i = 0;
	while (cmd->command[++i])
	{
		if (invalid_export(cmd->command[i], &status))
			continue ;
		keyvalue = split_var(cmd->command[i]);
		if (keyvalue == NULL)
			return (1);
		if (handle_export(keyvalue, env))
			return (1);
		free(keyvalue);
	}
	return (status);
}
