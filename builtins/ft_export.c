#include "minishell.h"

int	is_var(t_shell *sh, char *tmp)
{
	int	i;

	i = 0;
	while (sh && sh->envp && sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], tmp, ft_strlen(tmp)) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

void	norm_export(char **tmp, t_shell *sh, int i)
{
	char	*tmp2;

	if (tmp == NULL || sh->envp == NULL)
		return ;
	tmp2 = ft_strjoin(tmp[0], "=");
	free(sh->envp[i]);
	if (tmp[1] == NULL)
		sh->envp[i] = ft_strdup(tmp2);
	else
		sh->envp[i] = ft_strjoin(tmp2, tmp[1]);
	free(tmp2);
}

void	replace_value(t_shell *sh, char **tmp)
{
	int	i;

	i = 0;
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], tmp[0], ft_strlen(tmp[0])) == 0)
			norm_export(tmp, sh, i);
		i++;
	}
}

char	**create_value(t_shell *sh, char *av)
{
	char	**tmp;
	int		i;

	i = 0;
	if (sh->envp == NULL || av == NULL)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *) * (get_tab_size(sh->envp) + 2));
	if (!tmp)
		return (NULL);
	while (sh->envp[i])
	{
		tmp[i] = ft_strdup(sh->envp[i]);
		i++;
	}
	tmp[i] = ft_strdup(av);
	tmp[i + 1] = NULL;
	return (tmp);
}

void	reduce_builtexport(char **tmp, t_shell *sh, char *av)
{
	free_tab(tmp);
	tmp = create_value(sh, av);
	free_tab(sh->envp);
	sh->envp = tmp;
}

int	ft_export(t_cmd *c, t_shell *sh)
{
	char	**tmp;
	int		i;

	i = 1;
	if (get_tab_size(c->command) > 1)
	{
		while (c->command[i])
		{
			tmp = ft_split(c->command[i], '=');
			if (is_var(sh, tmp[0]) == EXIT_SUCCESS)
			{
				replace_value(sh, tmp);
				free_tab(tmp);
			}
			else
				reduce_builtexport(tmp, sh, c->command[i]);
			i++;
		}
	}
	free_tab(c->command);
    g_exit_code = 0;
	return (EXIT_SUCCESS);
}
