/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmachrou <wmachrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:54:29 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/04 19:00:12 by wmachrou         ###   ########.fr       */
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

void	free_prev(char **tab, size_t nb_words)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (i < nb_words)
		free(tab[i]);
	free(tab);
}

int	free_cmdline(t_shell *sh)
{
	free(sh->cmdline);
	sh->cmdline = readline(PROMPT);
	return (0);
}
