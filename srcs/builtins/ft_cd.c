/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:56:30 by stevennke         #+#    #+#             */
/*   Updated: 2025/02/03 13:28:49 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwd_vars(t_env **envp)
{
	char	*cwd;
	char	*pwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		pwd = envp_keytovalue("PWD", *envp, ft_strlen("PWD"));
		ft_override_env("OLDPWD", pwd, envp);
		ft_override_env("PWD", cwd, envp);
		free(cwd);
	}
}

static int	change_to_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_fprintf(2, "cd: HOME not set\n");
		return (EXIT_FAILURE);
	}
	if (chdir(home) == -1)
	{
		ft_fprintf(2, "minishell: cd %s: %s\n", home, strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	change_to_previous(t_env **envp)
{
	char	*oldpwd;

	oldpwd = envp_keytovalue("OLDPWD", *envp, ft_strlen("OLDPWD"));
	if (!oldpwd)
	{
		ft_fprintf(2, "cd: OLDPWD not set\n");
		return (EXIT_FAILURE);
	}
	if (chdir(oldpwd) == -1)
	{
		ft_fprintf(2, "minishell: cd %s: %s\n", oldpwd, strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	handle_tilde_path(const char *path, char *home)
{
	char	*full_path;
	int		ret;

	if (!home)
	{
		ft_fprintf(2, "cd: HOME not set\n");
		return (EXIT_FAILURE);
	}
	if (path[1])
	{
		full_path = ft_strjoin(home, path + 1);
		ret = chdir(full_path);
		free(full_path);
		if (ret == -1)
		{
			ft_fprintf(2, "minishell: cd %s: %s\n", path, strerror(errno));
			return (EXIT_FAILURE);
		}
	}
	else if (chdir(home) == -1)
	{
		ft_fprintf(2, "minishell: cd %s: %s\n", path, strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_cd(char **cmd, t_env **envp)
{
	int	ret;

	if (cmd && cmd[1] && cmd[2])
	{
		ft_fprintf(2, "cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	if (cmd && !cmd[1])
		ret = change_to_home();
	else if (!ft_strncmp(cmd[1], "-", 1))
		ret = change_to_previous(envp);
	else if (cmd[1][0] == '~')
		ret = handle_tilde_path(cmd[1], getenv("HOME"));
	else if (chdir(cmd[1]) == -1)
	{
		ft_fprintf(2, "minishell: cd %s: %s\n", cmd[1], strerror(errno));
		ret = EXIT_FAILURE;
	}
	else
		ret = EXIT_SUCCESS;
	if (ret == EXIT_SUCCESS)
		update_pwd_vars(envp);
	return (ret);
}
