/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:56:30 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/02 22:05:10 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void update_pwd_vars(t_env **envp)
{
    char *cwd;
    char *pwd;

    cwd = getcwd(NULL, 0);
    if (cwd)
    {
		pwd = envp_keytovalue("PWD", *envp, ft_strlen("PWD"));
		ft_override_env("OLDPWD", pwd, envp);
		ft_override_env("PWD", cwd, envp);
        free(cwd);
    }
}

int	ft_cd(char **cmd, t_env **envp)
{
	char	*home;

	if (cmd && cmd[1] && cmd[2])
	{
		ft_fprintf(2, "cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	if (cmd && !cmd[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			perror("HOME not set");
			return (EXIT_FAILURE);
		}
		if (chdir(home) == -1)
		{
			perror("chdir");
			return (EXIT_FAILURE);
		}
	}
    else if (cmd && cmd[1])
    {
        if (!ft_strncmp(cmd[1], "-", 1))
        {
            char *oldpwd = envp_keytovalue("OLDPWD", *envp, ft_strlen("OLDPWD"));
            if (!oldpwd)
            {
                ft_fprintf(2, "cd: OLDPWD not set\n");
                return (EXIT_FAILURE);
            }
            if (chdir(oldpwd) == -1)
            {
                perror("chdir");
                return (EXIT_FAILURE);
            }
        }
        else if (cmd[1][0] == '~')
        {
            char *home = getenv("HOME");
            if (!home)
            {
                ft_fprintf(2, "cd: HOME not set\n");
                return (EXIT_FAILURE);
            }
            if (cmd[1][1])
            {
                char *path = ft_strjoin(home, cmd[1] + 1);
                if (chdir(path) == -1)
                {
                    perror("chdir");
                    free(path);
                    return (EXIT_FAILURE);
                }
                free(path);
            }
            else if (chdir(home) == -1)
            {
                perror("chdir");
                return (EXIT_FAILURE);
            }
        }
        else if (chdir(cmd[1]) == -1)
        {
            perror("chdir");
            return (EXIT_FAILURE);
        }
    }
	update_pwd_vars(envp);
	return (EXIT_SUCCESS);
}