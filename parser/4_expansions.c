/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_expansions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:18:30 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/25 05:14:39 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_matching_var(t_node **iterator, t_env_var *vars)
{
	t_env_var	*env_var;
	char		*expanded;

	expanded = NULL;
	(*iterator) = (*iterator)->next;
	env_var = vars;
	while (env_var)
	{
		if (ft_strncmp((*iterator)->word, env_var->key,
				ft_strlen((*iterator)->word)) == 0)
		{
			expanded = env_var->value;
			break ;
		}
		env_var = env_var->next;
	}
	return (expanded);
}

void	handle_expands(t_node **tokens, t_env_var *vars)
{
	t_node	*iterator;
	char	*to_print;

	iterator = *tokens;
	while (iterator)
	{
		if (iterator->type == DOLLAR)
		{
			to_print = find_matching_var(&iterator, vars);
			printf("[%s]\n", to_print);
			return ;
		}
		iterator = iterator->next;
	}
}

int main(int ac, char *av[], char *envp[])
{
	char	*cmdline = "  \"COOOL\" CO |>>>\"$USER\" '||' \\ ? > ";
	t_node	*src;
	t_node	*dest;
	t_env_var 	*env;

	(void)ac;
	(void)av;
	src = NULL;
	characters_to_lst(cmdline, &src);
	printf("==================================================================\n");
	dest = NULL;
	words_to_lst(src, &dest);
	syntax_errors(dest);
	env = NULL;
	env = create_env_lst(envp, &env);
	handle_expands(&dest, env);
	delete_lst(&src);
	delete_lst(&dest);
	delete_lst_var(&env);
	return (0);
}
