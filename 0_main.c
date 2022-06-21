/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:58:40 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/21 20:53:05 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int mini_parsing(t_shell *sh, char *cmdline)
{
    
}

int main(void)
{
    t_shell *sh;

    sh = (t_shell *)malloc(sizeof(t_shell));
    if (!sh)
        return (-1);
    while (1)
	{
		sh->cmdline = readline("validate_my_minishell_pls>$ ");
        if (!sh->cmdline)
            return (-1);
        if (mini_parsing(sh, sh->cmdline) == -1)
            return (-1);
    }
    return (0);
}