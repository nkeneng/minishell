/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:22:19 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/03 15:15:22 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>

static void	container_child(t_shell *shell, int pipefd[2], char *dlm,
		int filekind)
{
	signal_dfl(SIGINT);
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(pipefd[1]);
		clean_exit(rperror("dup2"), shell);
	}
	close(pipefd[1]);
	clean_exit(here_doc(shell, dlm, filekind), shell);
}

static pid_t	container_parent(pid_t cpid, int pipefd[2])
{
	int	status;
	int	exit_status;

	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		return (rperror("dup2"));
	}
	close(pipefd[0]);
	waitpid(cpid, &status, 0);
	init_signals_when_children();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_signal = SIGINT;
		return (EXIT_FAILURE);
	}
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
			return (exit_status);
	}
	return (EXIT_SUCCESS);
}

/**
 * container
 * ---------
 * Creates a pipe, forks a child to run a here_doc, and redirects stdin.
 * Returns EXIT_SUCCESS on success or an error code otherwise.
 */
pid_t	container(t_shell *shell, char *dlm, int filekind)
{
	int		pipefd[2];
	pid_t	cpid;

	init_signals_heredoc();
	if (pipe(pipefd) == -1)
		return (rperror("pipe"));
	cpid = fork();
	if (cpid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (rperror("fork"));
	}
	if (cpid == 0)
		container_child(shell, pipefd, dlm, filekind);
	return (container_parent(cpid, pipefd));
}

int	start_pipex(t_list **cmd_list, t_shell *shell)
{
	int	exit_code;

	if (!cmd_list)
		return (rperror("command list empty"));
	exit_code = pipex(shell, cmd_list);
	reopen_stdin();
	reopen_stdout();
	return (exit_code);
}

int	open_doc(t_shell *shell, char *file, int filekind)
{
	int	fd;

	if (filekind & C_OPEN_INFILE)
	{
		fd = open(file, O_RDONLY, 0444);
		if (fd == -1)
			return (rperror("open"));
		if (dup2(fd, STDIN_FILENO) == -1)
			return (rperror("dup2"));
		close(fd);
		return (0);
	}
	else if (filekind & C_HERE_DOC)
		return (container(shell, file, filekind));
	else if (filekind & C_OPEN_OUT_TRUNC)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		return (rperror("open"));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (rperror("dup2"));
	close(fd);
	return (0);
}
