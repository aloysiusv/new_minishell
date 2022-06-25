/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:58:40 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/25 04:31:01 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code = 0;

int     parsing(t_shell *sh, t_node **tokens)
{
    
}

void    mini_loop(t_shell *sh)
{
    t_node  *tokens;

    while (1)
	{
		// signal(SIGINT, handle_sigs);
		// signal(SIGQUIT, handle_sigs);
        tokens = NULL;
        sh->cmdline = readline("pls_validate_minishell$> ");
        if (!sh->cmdline)
            free(sh->cmdline);
        if (sh->cmdline && ft_strlen(sh->cmdline) > 0)
			add_history(sh->cmdline);
        if (parsing(sh, &tokens) == -1)
            return ;
        if (ft_strncmp(sh->cmdline, "exit", 5))
            return ;
    }
    delete_lst(&tokens);
}

int main(int ac, char *av[], char *envp[])
{
    t_shell     *sh;
    t_env_var   *env_var;

    (void)av;
    if (ac > 1)
    {
        ft_putstr_fd("minishell: error", 2);
        ft_putstr_fd(": Too many arguments\n", 2);
        return (127);
    }
    sh = (t_shell *)ft_calloc(1, sizeof(t_shell));
    if (!sh)
        return (EXIT_FAILURE);
    sh->envp = create_env_lst(envp, env_var);
    mini_loop(sh);
    delete_lst_var(&env_var);
    free_shell(sh);
    return (0);
}