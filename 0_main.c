/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:58:40 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/24 06:43:17 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code = 0;

void    mini_loop(t_shell *sh)
{
    t_node  *tokens;

    while (1)
	{
		// signal(SIGINT, handle_sigs);
		// signal(SIGQUIT, handle_sigs);
        sh->cmdline = readline("pls_validate_minishell$> ");
        if (!sh->cmdline)
            free(sh->cmdline);
        if (sh->cmdline && ft_strlen(sh->cmdline) > 0)
			add_history(sh->cmdline);
        if (parsing(sh, sh->cmdline) == -1)
            return ;
    }
}

int main(int ac, char *av[], char *envp[])
{
    t_shell *sh;

    (void)av;
    if (ac > 1)
    {
        ft_putstr_fd("minishell: error", 2);
        ft_putstr_fd(": Too many arguments\n", 2);
        return (127);
    }
    sh = (t_shell *)malloc(sizeof(t_shell));
    if (!sh)
        return (-1);
    ft_memset(sh, 0, sizeof(t_shell));
    sh->envp = create_env(envp);
    mini_loop(sh);
    free_shell(sh);
    return (0);
}