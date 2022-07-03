/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:56:22 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/02 19:38:06 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_dir(char *command_name, char *path, t_dirp dirp)
{
	t_direntp	direntp;

	direntp = readdir(dirp);
	while (direntp != NULL)
	{
		if (!ft_strcmp(command_name, direntp->d_name))
			return (ft_strsjoin((char *[]){path, command_name, NULL}, "/"));
		direntp = readdir(dirp);
	}
	return (NULL);
}

static char	*open_dirs(char *command_name, char **paths)
{
	char		*command;
	t_dirp		dirp;
	size_t		i;

	command = NULL;
	i = 0;
	while (!command && paths[i])
	{
		dirp = opendir(paths[i]);
		if (dirp != NULL)
		{
			command = read_dir(command_name, paths[i], dirp);
			closedir(dirp);
		}
		i++;
	}
	return (command);
}

char	*resolve_path(char *command_name, char *path_value)
{
	char	**paths;
	char	*command;
	t_stat	buf;

	paths = ft_split(path_value, ':');
	if (paths == NULL)
		return (NULL);
	command = open_dirs(command_name, paths);
	ft_free_strs(paths);
	if (command == NULL)
		return (NULL);
	if (!stat(command, &buf) && S_ISDIR(buf.st_mode))
	{
		free(command);
		return (NULL);
	}
	return (command);
}
