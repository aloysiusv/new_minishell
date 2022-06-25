/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:34:47 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/25 03:18:53 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_shell(t_shell *sh)
{
	if (sh->cmdline)
		free(sh->cmdline);
	if (sh->envp)
		free_tab(sh->envp);
	if (sh->env_var)
		delete_lst(&sh->env_var);
	free(sh);
}
