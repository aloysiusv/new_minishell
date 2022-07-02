#include "minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd("pwd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_code = 1;
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
		g_exit_code = 0;
	}
	return (EXIT_SUCCESS);
}

void	update_pwd(char *oldpwd, char *pwd, char *pwd_ptr)
{
	pwd = getenv("PWD");
	oldpwd = getenv("OLDPWD");
	if (oldpwd != NULL && pwd != NULL)
		ft_strlcpy(oldpwd, pwd, ft_strlen(oldpwd));
	if (pwd != NULL)
	{
		pwd_ptr = getcwd(NULL, 0);
		ft_strlcpy(pwd, pwd_ptr, ft_strlen(pwd));
		free(pwd_ptr);
		pwd_ptr = NULL;
	}
}

void	home(char *pwd)
{
	pwd = getenv("HOME");
	chdir(pwd);
}

int	ft_cd(t_cmd *c)
{
	char	*oldpwd;
	char	*pwd;
	char	*pwd_ptr;

	oldpwd = NULL;
	pwd = NULL;
	pwd_ptr = NULL;
    if (ft_strncmp(c->command[0], "cd", 3) == 0 && !c->command[1])
		home(pwd);
	else
	{
        if (chdir(c->command[1]) == 0)
			update_pwd(oldpwd, pwd, pwd_ptr);
		else
		{
			perror("chdir");
			g_exit_code = 1;
		}
	}
	free_tab(c->command);
	g_exit_code = 0;
	return (EXIT_SUCCESS);
}
