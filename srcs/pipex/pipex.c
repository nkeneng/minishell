/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:22:19 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/19 14:45:39 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO: Katze: command not found \n execve: No such file or directory <to>
// minishell: command not found: Katze
// TODO: return exit code 130 from here_doc on cntl
	// + D (by child process or by manually returning)
// TODO: string expansion in here_doc
// TODO: macro values for fileindicator: < for input, > for output,
	// >> for append
// TODO: make pipex use linked list instead of double array
int	start_pipex(t_list **cmd_list, char *envp[])
{
	(void)envp;
	// dummy_cmd_list(cmd_list, 3, "ls -la", 0, "grep .c", 0, "wc -l", 0);
	// dummy_cmd_list(cmd_list, 1, "exit", C_BUILTIN);
	if (!cmd_list)
		return (rperror("command list empty"));
	return (pipex(envp, cmd_list));
}

// opens file, dup2s over correct std fd, filekind 0:inf, 1:outf, 2:outf(append)
int	open_doc(char *file, int filekind)
{
	int	fd;

	if (filekind == 0)
	{
		fd = open(file, O_RDONLY, 0444);
		if (fd == -1)
			exit(rperror("open"));
		if (dup2(fd, STDIN_FILENO) == -1)
			exit(rperror("dup2"));
		close(fd);
		return (0);
	}
	if (filekind == 1)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		exit(rperror("open"));
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

int	input_checker(int argc, char *arg)
{
	if (argc <= 4)
	{
		ft_fprintf(2, "pipex: parse error\n");
		exit(0);
	}
	else if (ft_strncmp("here_doc", arg, 8) == 0)
	{
		if (argc < 6)
		{
			ft_fprintf(2, "pipex: parse error\n");
			exit(0);
		}
		else
			return (2);
	}
	return (1);
}
