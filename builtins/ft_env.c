#include "minishell.h"

int	ft_env(char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			ft_putchar_fd(envp[i][j], 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
	g_exit_code = 0;
	return (EXIT_SUCCESS);
}
