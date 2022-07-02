#include "minishell.h"

int	only_digit(char *av)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (av[i])
	{
		while (av[i] == '-' || av[i] == '+')
		{
			i++;
			count++;
		}
		while (av[i])
		{
			if (!ft_isdigit(av[i]))
				return (0);
			i++;
		}
		if (count > 1)
			return (3);
	}
	return (1);
}

int	free_exit(t_shell *sh, int code)
{
    free_shell(sh);
	rl_clear_history();
	exit(code);
}

int	ft_exit(t_cmd *c, t_shell *sh)
{
	if (get_tab_size(c->command) == 1)
	{
		ft_putstr_fd("exit\n", 1);
		free_exit(sh, EXIT_SUCCESS);
	}
	else if (get_tab_size(c->command) > 2 && \
	only_digit(c->command[1]) == 1)
	{
		ft_putstr_fd("exit : too many arguments\n", 2);
		g_exit_code = 1;
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		if (only_digit(c->command[1]) == 1)
            free_exit(sh, ft_atoi(c->command[1]));
        else
		{
			printf("exit: %s : numeric arg required\n", c->command[1]);
			free_exit(sh, 255);
		}
	}
	return (EXIT_SUCCESS);
}
