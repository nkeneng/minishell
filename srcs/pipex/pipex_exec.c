/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:00:49 by admin             #+#    #+#             */
/*   Updated: 2025/01/11 05:00:50 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_builtin_stdout(t_shell *shell, t_command *cmd, int builtin_nb)
{
	if (handle_redirects(shell, cmd,
			C_HERE_DOC | C_OPEN_INFILE | C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP))
		return (EXIT_FAILURE);
	return (exec_builtin(builtin_nb, cmd, &(shell->envp), shell));
}

void	child_exec_to_stdout(t_shell *shell, t_command *cmd, int builtin_nb,
		int prev_fd)
{
	char	**envp_array;

	init_signals_noninteractive();
	if (prev_fd != -1 && !(has_flags(cmd, C_HERE_DOC | C_OPEN_INFILE)))
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			clean_exit(rperror("dup2"), shell);
		close(prev_fd);
	}
	if (handle_redirects(shell, cmd, C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP))
		clean_exit(EXIT_FAILURE, shell);
	if (builtin_nb)
		clean_exit(exec_builtin(builtin_nb, cmd, &(shell->envp), shell), shell);
	{
		envp_array = env_to_array(shell->envp);
		if (!envp_array)
			clean_exit(EXIT_FAILURE, shell);
		errno = make_exec(cmd, envp_array);
		clean_exit(errno, shell);
	}
}

int	exec_to_stdout(t_shell *shell, t_command *cmd, int chld_pids, int prev_fd)
{
	pid_t	cpid;
	int		status;
	int		builtin_nb;

	builtin_nb = is_builtin(cmd->cmd[0]);
	if (chld_pids == 1 && builtin_nb)
		return (handle_builtin_stdout(shell, cmd, builtin_nb));
	if (handle_redirects(shell, cmd, C_HERE_DOC | C_OPEN_INFILE))
		return (EXIT_FAILURE);
	cpid = fork();
	if (cpid == -1)
		return (rperror("fork"));
	else if (cpid == 0)
		child_exec_to_stdout(shell, cmd, builtin_nb, prev_fd);
	if (prev_fd != -1)
		close(prev_fd);
	waitpid(cpid, &status, 0);
	while (chld_pids--)
		waitpid(chld_pids, NULL, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

void	handle_child_input(t_shell *shell, t_command *cmd, int prev_fd,
		int *pipefd)
{
	if (prev_fd != -1 && !(has_flags(cmd, C_HERE_DOC | C_OPEN_INFILE)))
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			clean_exit(rperror("dup2"), shell);
		close(prev_fd);
	}
	if (pipefd)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit(rperror("dup2"));
		close(pipefd[1]);
		close(pipefd[0]);
	}
}

void	handle_child_exec(t_shell *shell, t_command *cmd, t_env **envp)
{
	char	**envp_array;

	if (cmd->flags & C_BUILTIN)
		clean_exit(exec_builtin(is_builtin(cmd->cmd[0]), cmd, envp, shell),
			shell);
	else
	{
		envp_array = env_to_array(*envp);
		if (!envp_array)
			exit(EXIT_FAILURE);
		make_exec(cmd, envp_array);
	}
}
