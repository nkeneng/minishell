/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:42:30 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/26 13:14:02 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * TODO handle cd error code
 */
//TODO: this is not exiting the child process properly. It needs to get one more argument, pid, that when 0 exits instead of returning, to behave like execve calls
//either this, or i somehow kill all children in the parent process
void handle_builtin(t_command *command, char *envp[])
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
	// else if (ft_strncmp(command->cmd[0], "export", ft_strlen("export")) == 0)
	// {
	// 	ft_export(command->cmd);
	// 	return ;
	// }
	// else if (ft_strncmp(command->cmd[0], "unset", ft_strlen("unset")) == 0)
	// {
	// 	ft_unset(command->cmd);
	// 	return ;
	// }
	else if (ft_strncmp(command->cmd[0], "env", ft_strlen("env")) == 0)
		ft_env(envp);
	else if (ft_strncmp(command->cmd[0], "exit", ft_strlen("exit")) == 0)
		ft_exit();
}

int	exec_command(t_command *command, char *envp[], int *fd)
{
	pid_t	cpid;

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
			make_exec(command, envp);
		exit(errno);
	}
	return (cpid);
}

int	pipex(char **envp, t_list **cmd_list)
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

// TODO: When handle_builtins is called, the child process should exit properly, instead of perroring.
//
// FIX: change needed in main: waiting for all children to make cat | cat | ls work
// while (tmp_list->next)
// 	waitpid(-1, NULL, 0);  //this is equal to wait(NULL);
// this will wait for all children to finish before the parent process finishes
// all children will terminate as they write to a pipe that has already been closed, they get the SIGPIPE signal and terminate
int	exec_to_stdout(char **envp, t_command *cmd)
{
	pid_t	cpid;
	int		status;

	cpid = fork();
	if (cpid == -1)
		return (rperror("fork"));
	else if (cpid == 0)
	{
		if (cmd->flags & C_BUILTIN)
			handle_builtin(cmd,envp);
		else
			make_exec(cmd, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(cpid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}
