/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:00:40 by admin             #+#    #+#             */
/*   Updated: 2025/01/11 05:00:42 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipex_child(t_command *cmd, int prev_fd, int *pipefd, t_shell *shell)
{
	t_env	**envp;

	envp = &(shell->envp);
	init_signals_noninteractive();
	handle_child_input(shell, cmd, prev_fd, pipefd);
	if (handle_redirects(shell, cmd, C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP))
		clean_exit(EXIT_FAILURE, shell);
	handle_child_exec(shell, cmd, envp);
	clean_exit(errno, shell);
}

int	setup_pipfd(int (*pipefd)[2], int prev_fd)
{
	close(*pipefd[1]);
	if (dup2(*pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
	}
	close(*pipefd[0]);
	if (prev_fd != -1)
	{
		close(prev_fd);
		prev_fd = -1;
	}
	return (prev_fd);
}

int	handle_in_redirects(t_shell *shell, t_command *cmd, int *pipefd,
		int *prev_fd)
{
	if (pipe(pipefd) == -1)
		return (rperror("pipe"));
	if (handle_redirects(shell, cmd, C_HERE_DOC | C_OPEN_INFILE))
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
		}
		close(pipefd[0]);
		if (*prev_fd != -1)
		{
			close(*prev_fd);
			*prev_fd = -1;
		}
		return (1);
	}
	return (0);
}

int	fork_child(t_shell *shell, t_command *cmd, int prev_fd, int *pipefd)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid == -1)
		return (rperror("fork"));
	else if (cpid == 0 && g_signal == 0)
	{
		pipex_child(cmd, prev_fd, pipefd, shell);
	}
	return (cpid);
}
