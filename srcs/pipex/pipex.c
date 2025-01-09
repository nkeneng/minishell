/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:22:19 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/09 18:12:15 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>

// int	start_pipex(t_list **cmd_list, t_shell *shell)
// {
// 	int	exit_code;
//
// 	if (!cmd_list)
// 		return (rperror("command list empty"));
// 	exit_code = pipex(shell, cmd_list);
// 	reopen_stdin();
// 	reopen_stdout();
// 	return (exit_code);
// }

int	start_pipex(t_list **cmd_list, t_shell *shell)
{
	int	exit_code;
	int	original_stdin;
	int	original_stdout;

	if (!cmd_list)
		return (rperror("command list empty"));
	original_stdin = dup(STDIN_FILENO);
	if (original_stdin == -1)
		return (rperror("dup"));
	original_stdout = dup(STDOUT_FILENO);
	if (original_stdout == -1)
	{
		close(original_stdin);
		return (rperror("dup"));
	}
	exit_code = pipex(shell, cmd_list);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	return (exit_code);
}

pid_t	container(t_shell *shell, char *dlm, int filekind)
{
	int		pipefd[2];
	pid_t	cpid;
	int		status;

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
	{
		signal_dfl(SIGINT);
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			close(pipefd[1]);
			exit(rperror("dup2"));
		}
		close(pipefd[1]);
		exit(here_doc(shell, dlm, filekind));
	}
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
		int exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
			return (exit_status);
	}
	return (EXIT_SUCCESS);
}

// // checks for permission first and only opens file if permission is granted
// int	open_with_perm(const char *file, int oflag, int perm)
// {
// 	// struct stat	st;
// 	int	fd;
//
// 	if (access(file, F_OK) == 0)
// 	{
// 		if (access(file, oflag) == -1)
// 		{
// 			perror("Permission denied");
// 			return (-1);
// 		}
// 		else if (errno != ENOENT) 
// 		{
// 			perror(file);
// 			return -1;
//     	}
// 	}
// 	fd = open(file, oflag, perm));
// 	if (fd == -1)
// 		return (rperror("open"));
// 	return (fd);
// }

// opens file, dup2s over correct std fd or executes heredoc
// heredoc gets opened with expand set to the oposite of quotation status
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
