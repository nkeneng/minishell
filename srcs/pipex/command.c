/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:42:30 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/16 16:34:10 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **env_to_array(t_env *envp)
{
	char	**envp_array;
	int		i;

	i = 0;
	envp_array = malloc(sizeof(char *) * (ft_env_size(envp) + 1));
	if (!envp_array)
		return (NULL);
	while (envp[i].key)
	{
		envp_array[i] = ft_strjoin3(envp[i].key, "=", envp[i].value);
		if (!envp_array[i])
			return (NULL);
		i++;
	}
	envp_array[i] = NULL;
	return (envp_array);
}

/**
 * TODO handle cd error code
 */
void handle_builtin(t_command *command, t_env **envp)
{
	if (ft_strncmp(command->cmd[0], "cd", ft_strlen("cd")) == 0)
		ft_cd(command->cmd[1]);
	else if (ft_strncmp(command->cmd[0], "echo", ft_strlen("echo")) == 0)
	{
		if (ft_strncmp(command->cmd[1], "-n", ft_strlen("-n")) == 0)
			ft_echo(command->cmd, 1);
		else
			ft_echo(command->cmd, 0);
	}
	else if (ft_strncmp(command->cmd[0], "pwd", ft_strlen("pwd")) == 0)
		ft_pwd();
	else if (ft_strncmp(command->cmd[0], "export", ft_strlen("export")) == 0)
		ft_export(command->cmd, envp);
	// else if (ft_strncmp(command->cmd[0], "unset", ft_strlen("unset")) == 0)
	// {
	// 	ft_unset(command->cmd);
	// 	return ;
	// }
	else if (ft_strncmp(command->cmd[0], "env", ft_strlen("env")) == 0)
		ft_env(env_to_array(*envp));
	else if (ft_strncmp(command->cmd[0], "exit", ft_strlen("exit")) == 0)
		ft_exit();
}

int	exec_command(t_command *command, t_env **envp, int *fd)
{
	pid_t	cpid;
	char **envp_array;

	cpid = fork();
	if (cpid == -1)
		return (rperror("fork"));
	else if (cpid == 0)
	{
		close(fd[0]);
		if (fd[1] != STDOUT_FILENO)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				return (rperror("dup2"));
			close(fd[1]);
		}
		if (command->flags & C_BUILTIN)
			handle_builtin(command, envp);
		else
		{
			envp_array = env_to_array(*envp);
			make_exec(command, envp_array);
		}
		exit(errno);
	}
	return (cpid);
}

int	pipex(t_env **envp, t_list **cmd_list)
{
	int		pipefd[2];
	pid_t	cpid;
	t_list	*tmp_list;

	tmp_list = *cmd_list;
	while (tmp_list->next)
	{
		if (pipe(pipefd) == -1)
			return (rperror("pipe"));
		cpid = exec_command(tmp_list->content, envp, pipefd);
		if (cpid == -1)
			return (rperror("fork"));
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			return (rperror("dup2"));
		close(pipefd[0]);
		tmp_list = tmp_list->next;
	}
	close(pipefd[0]);
	return (exec_to_stdout(envp, ft_lstlast(*cmd_list)->content));
}

int	exec_to_stdout(t_env **envp, t_command *cmd)
{
	pid_t	cpid;
	int		status;
	char **envp_array;

	cpid = fork();
	if (cpid == -1)
		return (rperror("fork"));
	else if (cpid == 0)
	{
		if ((cmd->flags & C_BUILTIN))
			handle_builtin(cmd,envp);
		else
		{
			envp_array = env_to_array(*envp);
			make_exec(cmd, envp_array);
		}
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(cpid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}
