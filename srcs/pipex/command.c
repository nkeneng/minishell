/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:42:30 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/09 08:15:08 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_for_children(int *chld_pids)
{
	int	status;
	int	i;

	i = 1;
	while (i < chld_pids[0])
	{
		waitpid(chld_pids[i], &status, 0);
		i++;
	}
	free(chld_pids);
	return (status);
}

int	exec_to_stdout(t_shell *shell, t_command *cmd, int *chld_pids, int prev_fd)
{
	pid_t	cpid;
	int		status;
	char	**envp_array;
	int		builtin_nb;
	t_env	**envp;

	envp = &(shell->envp);
	builtin_nb = is_builtin(cmd->cmd[0]);
	if (chld_pids[0] == 1 && builtin_nb)
	{
		if (handle_redirects(shell, cmd,
				C_HERE_DOC | C_OPEN_INFILE | C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP))
			return (EXIT_FAILURE);
		return (exec_builtin(builtin_nb, cmd, envp));
	}
	if (handle_redirects(shell, cmd, C_HERE_DOC | C_OPEN_INFILE))
		return (EXIT_FAILURE);
	cpid = fork();
	if (cpid == -1)
	{
		free(chld_pids);
		return (rperror("fork"));
	}
	else if (cpid == 0)
	{
		init_signals_noninteractive();
		if (prev_fd != -1 && !(has_flags(cmd, C_HERE_DOC | C_OPEN_INFILE)))
		{
			if (dup2(prev_fd, STDIN_FILENO) == -1)
				exit(rperror("dup2"));
			close(prev_fd);
		}
		if (handle_redirects(shell, cmd, C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP))
			exit(EXIT_FAILURE);
		if (builtin_nb)
			exit(exec_builtin(builtin_nb, cmd, envp));
		envp_array = env_to_array(*envp);
		if (!envp_array)
			exit(EXIT_FAILURE);
		errno = make_exec(cmd, envp_array);
		exit(errno);
	}
	if (prev_fd != -1)
		close(prev_fd);
	waitpid(cpid, &status, 0);
	wait_for_children(chld_pids);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

int	pipex(t_shell *shell, t_list **cmd_list)
{
	int			pipefd[2];
	t_env		**envp;
	pid_t		cpid;
	t_list		*tmp_list;
	t_command	*cmd;
	int			size;
	int			*pid_array;
	int			prev_fd;
	char		**envp_array;

	envp = &(shell->envp);
	prev_fd = -1;
	size = ft_lstsize(*cmd_list);
	pid_array = malloc(sizeof(int) * size);
	if (!pid_array)
		return (rperror("malloc"));
	pid_array[0] = size;
	size = 1;
	tmp_list = *cmd_list;
	init_signals_when_children();
	while (tmp_list->next)
	{
		if (pipe(pipefd) == -1)
			return (rperror("pipe"));
		if (handle_redirects(shell, tmp_list->content,
				C_HERE_DOC | C_OPEN_INFILE))
		{
			close(pipefd[1]);
			if (dup2(pipefd[0], STDIN_FILENO) == -1)
			{
				perror("dup2");
			}
			close(pipefd[0]);
			if (prev_fd != -1)
			{
				close(prev_fd);
				prev_fd = -1;
			}
			tmp_list = tmp_list->next;
			continue ;
		}
		cpid = fork();
		if (cpid == -1)
			return (rperror("fork"));
		else if (cpid == 0 && g_signal == 0)
		{
			init_signals_noninteractive();
			cmd = (t_command *)tmp_list->content;
			if (prev_fd != -1 && !(has_flags(cmd, C_HERE_DOC | C_OPEN_INFILE)))
			{
				if (dup2(prev_fd, STDIN_FILENO) == -1)
					exit(rperror("dup2"));
				close(prev_fd);
			}
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				exit(rperror("dup2"));
			close(pipefd[1]);
			close(pipefd[0]);
			if (handle_redirects(shell, cmd, C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP))
				exit(EXIT_FAILURE);
			if (cmd->flags & C_BUILTIN)
				exit(exec_builtin(is_builtin(cmd->cmd[0]), cmd, envp));
			else
			{
				envp_array = env_to_array(*envp);
				if (!envp_array)
					exit(EXIT_FAILURE);
				make_exec(cmd, envp_array);
			}
			exit(errno);
		}
		close(pipefd[1]);
		if (prev_fd != -1)
			close(prev_fd);
		prev_fd = pipefd[0];
		init_signals_when_children();
		tmp_list = tmp_list->next;
		pid_array[size++] = cpid;
	}
	return (exec_to_stdout(shell, ft_lstlast(*cmd_list)->content, pid_array,
			prev_fd));
}
