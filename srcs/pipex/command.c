/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:42:30 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/10 17:12:31 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **env_to_array(t_env *envp)
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

int	exec_builtin(int builtin, t_command *command, t_env **envp)
{
	if (builtin == CD_BUILTIN)
		return(ft_cd(command->cmd[1]));
	else if (builtin == ECHO_BUILTIN)
	{
		if (command->cmd[1] && ft_strncmp(command->cmd[1], "-n", ft_strlen("-n")) == 0)
			return(ft_echo(command->cmd, 1));
		else
			return(ft_echo(command->cmd, 0));
	}
	else if (builtin == PWD_BUILTIN)
		return(ft_pwd());
	else if (builtin == EXPORT_BUILTIN)
		return(ft_export(command->cmd, envp));
	else if (builtin == UNSET_BUILTIN)
		return (ft_unset(command->cmd, envp));
	else if (builtin == ENV_BUILTIN)
		return (ft_env(env_to_array(*envp)));
	else if (builtin == EXIT_BUILTIN)
		ft_exit();
	return (0);
}

//@TODO: handle heredoc signals not working yet
int	pipex(t_env **envp, t_list **cmd_list)
{
	int		pipefd[2];
	pid_t	cpid;
	t_list	*tmp_list;
	t_command *cmd;
	int	size;
	int	*pid_array;

	size = ft_lstsize(*cmd_list);
	pid_array = malloc(sizeof(int) * size);
	pid_array[0] = size;
	size = 1;
	tmp_list = *cmd_list;
	init_signals_when_children();
	while (tmp_list->next)
	{
		if (handle_redirects(tmp_list->content, C_HERE_DOC | C_OPEN_INFILE))
			return (EXIT_FAILURE);
		if (pipe(pipefd) == -1)
			return (rperror("pipe"));
		cpid = fork();
		if (cpid == -1)
			return (rperror("fork"));
		else if (cpid == 0 && g_signal == 0)
		{
			init_signals_noninteractive();
			cmd = (t_command *)tmp_list->content;
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				exit(rperror("dup2"));
			close(pipefd[1]);
			if (handle_redirects(cmd, C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP))
				return (EXIT_FAILURE);
			if (cmd->flags & C_BUILTIN)
				exit(exec_builtin(is_builtin(cmd->cmd[0]), cmd, envp));
			else
			{
				char **envp_array = env_to_array(*envp);
				make_exec(cmd, envp_array);
			}
			exit(errno);
		}
		init_signals_when_children();
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			return (rperror("dup2"));
		close(pipefd[0]);
		tmp_list = tmp_list->next;
		pid_array[size++] = cpid;
	}
	return (exec_to_stdout(envp, ft_lstlast(*cmd_list)->content, pid_array));
}

int	wait_for_children(int *chld_pids)
{
	int status;
	int i;

	i = 1;
	while (i < chld_pids[0])
	{
		waitpid(chld_pids[i], &status, 0);
		i++;
	}
	free(chld_pids);
	return (status);
}

int	exec_to_stdout(t_env **envp, t_command *cmd, int *chld_pids)
{
	pid_t	cpid;
	int		status;
	char	**envp_array;
	int		builtin_nb;

	builtin_nb = is_builtin(cmd->cmd[0]);
	if (chld_pids[0] == 1 && builtin_nb)
	{
		if (handle_redirects(cmd, C_HERE_DOC | C_OPEN_INFILE | C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP))
			return(EXIT_FAILURE);
		return (exec_builtin(builtin_nb, cmd, envp));
	}
	if (handle_redirects(cmd, C_HERE_DOC | C_OPEN_INFILE))
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
		if (handle_redirects(cmd, C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP))
			return (EXIT_FAILURE);
		if (builtin_nb)
			exit(exec_builtin(builtin_nb, cmd, envp));
		envp_array = env_to_array(*envp);
		if (!envp_array)
			exit(EXIT_FAILURE);
		errno = make_exec(cmd, envp_array);
		// perror("execve");
		exit(errno);
	}
	waitpid(cpid, &status, 0);
	wait_for_children(chld_pids);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status)) //probably remove this, cause i am doing this in main. exit with status in heredoc
		return (128 + WTERMSIG(status)); // we might not even need the global now that i think about it, cause we do all the exit signal operations ins main
	return (status);
}
