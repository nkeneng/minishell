/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:56:59 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/14 18:56:18 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_commpath(char **paths, const char *command, int *err)
{
	int		i;
	char	*commpath;

	i = 0;
	while (paths[i])
	{
		commpath = ft_strjoin3(paths[i++], "/", command);
		if (!commpath)
		{
			*err = 127;
			return (NULL);
		}
		else if (access(commpath, X_OK) == 0)
			return (commpath);
		free(commpath);
	}
	ft_fprintf(2, "%s: command not found\n", command);
	*err = 127;
	return (NULL);
}

char	**get_paths(char *envp[])
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

static int	check_command_slash(char **cmd)
{
	if (access(cmd[0], F_OK) != 0)
	{
		ft_fprintf(2, "%s: No such file or directory\n", cmd[0]);
		return (127);
	}
	if (access(cmd[0], X_OK) != 0 || access(cmd[0], R_OK) != 0)
	{
		ft_fprintf(2, "%s: Permission denied\n", cmd[0]);
		return (126);
	}
	return (checkdir(cmd[0]));
}

static char	*build_commpath(t_command *cmd, char *envp[], int *err)
{
	char	**paths;
	char	*commpath;
	char	**command;
	int		check_res;

	command = cmd->cmd;
	if (ft_strchr(command[0], '/'))
	{
		check_res = check_command_slash(command);
		if (check_res)
		{
			*err = check_res;
			return (NULL);
		}
		return (ft_strdup(command[0]));
	}
	paths = get_paths(envp);
	if (!paths)
	{
		*err = rperror("malloc");
		return (NULL);
	}
	commpath = get_commpath(paths, command[0], err);
	free_char_array(paths, 1);
	return (commpath);
}

int	make_exec(t_command *cmd, char *envp[])
{
	int		err;
	char	*commpath;
	char	**command;

	err = 0;
	command = cmd->cmd;
	commpath = build_commpath(cmd, envp, &err);
	if (!commpath)
		return (err);
	execve(commpath, command, envp);
	err = errno;
	ft_fprintf(2, "%s: %s\n", command[0], strerror(err));
	free(commpath);
	return (err);
}
