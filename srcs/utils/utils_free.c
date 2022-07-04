/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:54:29 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/03 23:04:32 by lrandria         ###   ########.fr       */
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

void    free_prev(char **tab, size_t nb_words)
{
    size_t	i;

    if (!tab)
		return ;
	i = 0;
	while (i < nb_words)
		free(tab[i]);
	free(tab);
}

// void	free_shell(t_shell *sh)
// {
// 	if (!sh)
// 		return ;
// 	if (sh->cmdline)
// 		free(sh->cmdline);
// 	if (sh->envp)
// 		free_tab(sh->envp);
// 	if (sh->all_paths)
// 		free_tab(sh->all_paths);
// 	if (sh->env_var)
// 		delete_lst_env(&sh->env_var);
// 	if (sh->chars)
// 		delete_lst(&sh->chars);
// 	if (sh->tokens)
// 		delete_lst(&sh->tokens);
// 	if (sh->cmds)
// 		delete_cmds_tab(sh);
// 	free(sh);
// }
