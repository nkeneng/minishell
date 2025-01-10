/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:42:30 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/10 16:09:12 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_to_stdout(t_shell *shell, t_command *cmd, int chld_pids, int prev_fd)
{
	pid_t	cpid;
	int		status;
	char	**envp_array;
	int		builtin_nb;
	t_env	**envp;

	envp = &(shell->envp);
	builtin_nb = is_builtin(cmd->cmd[0]);
	if (chld_pids == 1 && builtin_nb)
	{
		if (handle_redirects(shell, cmd,
				C_HERE_DOC | C_OPEN_INFILE | C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP))
			return (EXIT_FAILURE);
		return (exec_builtin(builtin_nb, cmd, envp, shell));
	}
	if (handle_redirects(shell, cmd, C_HERE_DOC | C_OPEN_INFILE))
		return (EXIT_FAILURE);
	cpid = fork();
	if (cpid == -1)
		return (rperror("fork"));
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
			exit(exec_builtin(builtin_nb, cmd, envp, shell));
		envp_array = env_to_array(*envp);
		if (!envp_array)
			exit(EXIT_FAILURE);
		errno = make_exec(cmd, envp_array);
		exit(errno);
	}
	if (prev_fd != -1)
		close(prev_fd);
	waitpid(cpid, &status, 0);
	while (chld_pids)
		waitpid(chld_pids--, NULL, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

void	pipex_child(t_command *cmd, int prev_fd, int *pipefd, t_shell *shell)
{
	char		**envp_array;
	t_env		**envp;

	envp = &(shell->envp);
	init_signals_noninteractive();
	if (prev_fd != -1 && !(has_flags(cmd, C_HERE_DOC | C_OPEN_INFILE)))
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			exit(rperror("dup2"));
		close(prev_fd);
	}
	if (pipefd)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit(rperror("dup2"));
		close(pipefd[1]);
		close(pipefd[0]);
	}
	if (handle_redirects(shell, cmd, C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP))
		exit(EXIT_FAILURE);
	if (cmd->flags & C_BUILTIN)
		clean_exit(exec_builtin(is_builtin(cmd->cmd[0]), cmd, envp, shell), shell);
	else
	{
		envp_array = env_to_array(*envp);
		if (!envp_array)
			exit(EXIT_FAILURE);
		make_exec(cmd, envp_array);
	}
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

int	pipex(t_shell *shell, t_list **cmd_list)
{
	int			pipefd[2];
	pid_t		cpid;
	t_list		*tmp_list;
	int			size;
	int			p_nb;
	int			prev_fd;

	prev_fd = -1;
	size = ft_lstsize(*cmd_list);
	p_nb = size;
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
			pipex_child(tmp_list->content, prev_fd, pipefd, shell);
		close(pipefd[1]);
		if (prev_fd != -1)
			close(prev_fd);
		prev_fd = pipefd[0];
		init_signals_when_children();
		tmp_list = tmp_list->next;
	}
	return (exec_to_stdout(shell, ft_lstlast(*cmd_list)->content, p_nb,
			prev_fd));
}
