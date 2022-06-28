/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get_expands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:18:30 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/28 16:13:48 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_matching_var(t_node *iterator, t_env *vars)
{
	t_env	*env_var;
	char	*expanded;

	expanded = NULL;
	env_var = vars;
	while (iterator && env_var)
	{
		if (ft_strncmp(iterator->word, env_var->key,
			ft_strlen(iterator->word)) == 0)
		{
			expanded = ft_strdup(env_var->value);
			break ;
		}
		if (env_var->next)
			env_var = env_var->next;
	}
	return (expanded);
}

void	get_expands(t_node **tokens, t_env *vars)
{
	t_node	*iterator;
	char	*to_print;

	iterator = *tokens;
	if (!iterator->next)
		return ;
	while (iterator)
	{
		if (iterator->type == DOLLAR)
		{
			iterator = iterator->next;
			// printf("[%s]\n", iterator->word);
			if (iterator->next->type == BLANK)
				break ;
			to_print = find_matching_var(iterator, vars);
			if (to_print)
			{
				free(iterator->word);
				iterator->word = ft_strdup(to_print);
				delete_specific_node(tokens, DOLLAR);
				free(to_print);
			}
		}
		if (iterator->next)
			iterator = iterator->next;
	}
}

// int main(int ac, char *av[], char *envp[])
// {
// 	char	*cmdline = "  \"COOOL\" CO |'$>'>>\"$USER\" '||' \\ ? > ";
// 	t_node	*src;
// 	t_node	*dest;
// 	t_env 	*env;

// 	(void)ac;
// 	(void)av;
// 	src = NULL;
// 	characters_to_lst(cmdline, &src);
// 	printf("==================================================================\n");
// 	dest = NULL;
// 	words_to_lst(src, &dest);
// 	syntax_errors(dest);
// 	env = NULL;
// 	env = create_env_lst(envp, &env);
// 	handle_expands(&dest, env);
// 	delete_lst(&src);
// 	delete_lst(&dest);
// 	delete_lst_var(&env);
// 	return (0);
// }
