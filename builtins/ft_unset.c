#include "minishell.h"


int	is_argument(char **av, char *env_var)
{
	int	i;

	i = 0;
	while (env_var && av && av[i])
	{
		if (ft_strncmp(av[i], env_var, ft_strlen(av[i])) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

char	**unset_copy(t_shell *sh, char **av, int count)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = malloc(sizeof(char *) * (get_tab_size(sh->envp) - count + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (sh->envp[i])
	{
		if (count && is_argument(av, sh->envp[i]) == EXIT_SUCCESS)
		{
			++i;
			--count;
		}
		else
			tmp[j++] = ft_strdup(sh->envp[i++]);
	}
	tmp[j] = NULL;
	return (tmp);
}

int	ft_unset(t_cmd *c, t_shell *sh)
{
	char	**to_free;
	int		i;
	int		count;

	i = 1;
	count = 0;
	while (sh && sh->envp && c->command && c->command[i])
	{
		if (is_var(sh, c->command[i]) == EXIT_SUCCESS)
			count++;
		i++;
	}
	if (count == 0)
	{
		free_tab(c->command);
		return (EXIT_SUCCESS);
	}
	to_free = sh->envp;
	sh->envp = unset_copy(sh, c->command, count);
	free_tab(to_free);
	free_tab(c->command);
	g_exit_code = 0;
	return (EXIT_SUCCESS);
}
