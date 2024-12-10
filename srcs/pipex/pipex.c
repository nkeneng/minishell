/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:22:19 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/10 12:26:38 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>

// TODO: return exit code 130 from here_doc on cntl
	// + D (by child process or by manually returning)
// TODO: string expansion in here_doc
// TODO: macro values for fileindicator: < for input, > for output,
	// >> for append
int	start_pipex(t_list **cmd_list, t_env **envp)
{
	int	exit_code;
	if (!cmd_list)
		return (rperror("command list empty"));
	exit_code = pipex(envp, cmd_list);
	close(STDIN_FILENO);
	if (open("/dev/tty", O_RDONLY) != STDIN_FILENO)
	{
		perror("Failed to reopen stdin");
		exit(EXIT_FAILURE);
	}
	close(STDOUT_FILENO);
	if (open("/dev/tty", O_WRONLY) != STDOUT_FILENO)
	{
		perror("Failed to reopen stdout");
		exit(EXIT_FAILURE);
	}
	return (exit_code);
}

pid_t container(char *dlm)
{
	int		pipefd[2];
	pid_t	cpid;
	int		status;

	// init_signals_when_children();
	// init_signals_noninteractive();
	init_signals_heredoc();
	if (pipe(pipefd) == -1)
		return (rperror("pipe"));
	cpid = fork();
	if (cpid == -1)
		return (rperror("fork"));
	else if (cpid == 0)
	{
		// init_signals_heredoc();
		if (!isatty(STDIN_FILENO))
		{
			close(STDIN_FILENO);
			if (open("/dev/tty", O_RDONLY) != STDIN_FILENO)
			{
				perror("Failed to reopen stdin");
				exit(EXIT_FAILURE); //exit with somethig negative else to diff from cpid
			}
		}
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit(rperror("dup2"));
		close(pipefd[1]);
		exit(here_doc(dlm));
	}
	// init_signals_when_children();
	// init_signals_noninteractive();
	// init_signals();
	close(pipefd[1]);
	if (g_signal != SIGINT)
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			return (rperror("dup2"));
	g_signal = 0;
	close(pipefd[0]);
	waitpid(cpid, &status, 0);
	return (status);
}

// opens file, dup2s over correct std fd or executes heredoc
int	open_doc(char *file, int filekind)
{
	int	fd;
	pid_t pid;

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
	{
		pid = container(file);
		return (0);
	}
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

int	pipheredoc(char *arg)
{
	pid_t	cpid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (rperror("pipe"));
	cpid = fork();
	if (cpid == -1)
		return (rperror("fork"));
	else if (cpid == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (rperror("dup2"));
		close(pipefd[1]);
		here_doc(arg);
		exit(0);
	}
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		return (rperror("dup2"));
	close(pipefd[0]);
	waitpid(cpid, NULL, 0);
	return (EXIT_SUCCESS);
}
