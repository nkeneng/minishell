/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:56:59 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/24 14:23:40 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_commpath(char **paths, const char *command)
{
	int		i;
	char	*commpath;

	i = 0;
	while (paths[i])
	{
		commpath = ft_strjoin3(paths[i++], "/", command);
		if (!commpath)
			return (NULL);
		else if (access(commpath, X_OK) == 0)
			return (commpath);
		free(commpath);
	}
	ft_fprintf(2, "%s: command not found\n", command);
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

// this needs to return properly and afterwards if failed free the whole list
int	make_exec(t_command *cmd, char *envp[])
{
	char	**paths;
	char	*commpath;
	char	**command;
	int		err;

	command = cmd->cmd;
	if (ft_strchr(command[0], '/') != NULL)
	{
		if (access(command[0], X_OK) == 0)
			commpath = ft_strdup(command[0]);
		else
		{
			ft_fprintf(2, "%s: command not found\n", command[0]);
			return (free_char_array(command, 127));
		}
	}
	else {
		paths = get_paths(envp);
		if (!paths)
		{
			free_char_array(paths, 1);
			return (rperror("malloc"));
		}
		commpath = get_commpath(paths, command[0]);
		free_char_array(paths, 1);
		if (!commpath)
			return (free_char_array(command, 127));
	}
	execve(commpath, command, envp);
	err = errno;
	ft_fprintf(2, "%s: %s\n", command[0], strerror(err));
	free(commpath);
	free_char_array(command, 1);
	return (err);
}
