/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:42:30 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/07 17:20:07 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_to_array(t_env *envp)
{
	char	**envp_array;
	int		i;

	i = 0;
	envp_array = malloc(sizeof(char *) * (ft_env_size(envp) + 1));
	if (!envp_array)
		return (NULL);
	while (envp[i].key)
	{
		envp_array[i] = ft_strjoin3(envp[i].key, "=", envp[i].value);
		if (!envp_array[i])
			return (NULL);
		i++;
	}
	envp_array[i] = NULL;
	return (envp_array);
}

int	exec_builtin(int builtin, t_command *command, t_env **envp, t_list **cmds)
{
	(void) cmds;
	if (builtin == CD_BUILTIN)
		return (ft_cd(command->cmd, envp));
	else if (builtin == ECHO_BUILTIN)
		return (ft_echo(command->cmd));
	else if (builtin == PWD_BUILTIN)
		return (ft_pwd());
	else if (builtin == EXPORT_BUILTIN)
		return (ft_export(command->cmd, envp));
	else if (builtin == UNSET_BUILTIN)
		return (ft_unset(command->cmd, envp));
	else if (builtin == ENV_BUILTIN)
		return (ft_env(env_to_array(*envp)));
	else if (builtin == EXIT_BUILTIN)
		return (ft_exit(command->cmd, cmds));
	return (0);
}

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

// uses stdout to hold the last pipe end, so stdin can read from pipe
void	dup_output_to_pipe(int *pipefd)
{
	if (pipefd != NULL)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit(rperror("dup2"));
		close(pipefd[1]);
		close(pipefd[0]);
	}
}

int	pipex_child(t_shell *shell, t_command *cmd, int *prev_fd, int *pipefd)
{
	char	**envp_array;

	init_signals_noninteractive();
	if (*prev_fd != -1 && !(has_flags(cmd, C_HERE_DOC | C_OPEN_INFILE)))
	{
		if (dup2(*prev_fd, STDIN_FILENO) == -1)
			exit(rperror("dup2"));
		close(*prev_fd);
	}
	dup_output_to_pipe(pipefd);
	if (handle_redirects(shell, cmd, C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP))
		exit(EXIT_FAILURE);
	if (cmd->flags & C_BUILTIN)
		exit(exec_builtin(is_builtin(cmd->cmd[0]), cmd, &(shell->envp), shell->cmd_list));
	else
	{
		envp_array = env_to_array(shell->envp);
		if (!envp_array)
			exit(EXIT_FAILURE);
		make_exec(cmd, envp_array);
	}
	exit(errno);
}

int	exec_to_stdout(t_shell *shell, t_list **cmds, int *chld_pids, int prev_fd)
{
	pid_t		cpid;
	int			status;
	int			builtin_nb;
	t_env		**envp;
	t_command	*cmd;

	envp = &(shell->envp);
	cmd = ft_lstlast(*cmds)->content;
	builtin_nb = is_builtin(cmd->cmd[0]);
	if (chld_pids[0] == 1 && builtin_nb)
	{
		if (handle_redirects(shell, cmd,
				C_HERE_DOC | C_OPEN_INFILE | C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP))
			return (EXIT_FAILURE);
		free(chld_pids);
		return (exec_builtin(builtin_nb, cmd, envp, cmds));
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
		pipex_child(shell, cmd, &prev_fd, NULL);
	if (prev_fd != -1)
		close(prev_fd);
	waitpid(cpid, &status, 0);
	wait_for_children(chld_pids);
	ft_lstclear(cmds, ft_free_command);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

int	pipex(t_shell *shell, t_list **cmd_list)
{
	int		pipefd[2];
	pid_t	cpid;
	t_list	*tmp_list;
	int		size;
	int		*pid_array;
	int		prev_fd;

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
				perror("dup2");
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
			pipex_child(shell, (t_command *)tmp_list->content, &prev_fd,
				pipefd);
		close(pipefd[1]);
		if (prev_fd != -1)
			close(prev_fd);
		prev_fd = pipefd[0];
		init_signals_when_children();
		tmp_list = tmp_list->next;
		pid_array[size++] = cpid;
	}
	return (exec_to_stdout(shell, cmd_list, pid_array, prev_fd));
}
