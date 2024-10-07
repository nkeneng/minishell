/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:42:30 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/07 17:12:00 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		make_exec(command, envp);
		exit(errno);
	}
	return (cpid);
}

int	pipex(char **envp, t_list *cmd_list)
{
	int		pipefd[2];
	pid_t	cpid;
	t_list	*tmp_list;

	tmp_list = cmd_list;
	while (tmp_list)
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
	return (1);
}

int	exec_to_stdout(char **envp, t_command *cmd)
{
	pid_t	cpid;
	int		status;

	cpid = fork();
	if (cpid == -1)
		return (rperror("fork"));
	else if (cpid == 0)
	{
		make_exec(cmd, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(cpid, &status, 0);
	close(STDOUT_FILENO);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}
