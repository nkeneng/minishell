/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:42:30 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/01 10:26:27 by lmeubrin         ###   ########.fr       */
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
// Add this helper function
static int has_output_redirection(t_list *redirects)
{
	while (redirects && redirects->content)
	{
		t_redirect *redir = redirects->content;
		if (redir->filename->flags & (W_OPEN_OUT_TRUNC | W_OPEN_OUT_APP))
			return (1);
		redirects = redirects->next;
	}
	return (0);
}

int	exec_builtin(int builtin, t_command *command, t_env **envp)
{
	if (builtin == CD_BUILTIN)
		return(ft_cd(command->cmd[1]));
	else if (builtin == ECHO_BUILTIN)
	{
		if (ft_strncmp(command->cmd[1], "-n", ft_strlen("-n")) == 0)
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

int	pipex(t_env **envp, t_list **cmd_list)
{
	int		pipefd[2];
	pid_t	cpid;
	t_list	*tmp_list;
	int		i;
	t_command *cmd;
	t_redirect *redir;

	tmp_list = *cmd_list;
	i = 0;
	while (tmp_list->next)
	{
		if (pipe(pipefd) == -1)
			return (rperror("pipe"));
		cpid = fork();
		if (cpid == -1)
			return (rperror("fork"));
		else if (cpid == 0)
		{
			cmd = (t_command *)tmp_list->content;
			t_list *redir_list;
			redir_list = cmd->redirects;
			close(pipefd[0]);
			while (redir_list && redir_list->content)
			{
				redir = redir_list->content;
				if (redir->filename->flags & (C_OPEN_INFILE | C_HERE_DOC))
				{
					ft_printf("opening input file %s\n", redir->filename->word);
					open_doc(redir->filename->word, redir->filename->flags);
				}
				else if (redir->filename->flags & (W_OPEN_OUT_TRUNC | W_OPEN_OUT_APP))
				{
					ft_printf("opening output file %s\n", redir->filename->word);
					open_doc(redir->filename->word, redir->filename->flags);
				}
				redir_list = redir_list->next;
			}
			if (!has_output_redirection(cmd->redirects))
			{
				if (dup2(pipefd[1], STDOUT_FILENO) == -1)
					exit(rperror("dup2"));
			}
			close(pipefd[1]);
			if (cmd->flags & C_BUILTIN)
				exit(exec_builtin(is_builtin(cmd->cmd[0]), cmd, envp));
			else
			{
				char **envp_array = env_to_array(*envp);
				make_exec(cmd, envp_array);
			}
			exit(errno);
		}
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			return (rperror("dup2"));
		close(pipefd[0]);
		tmp_list = tmp_list->next;
		i++;
	}
	return (exec_to_stdout(envp, ft_lstlast(*cmd_list)->content, i));
}


int	exec_to_stdout(t_env **envp, t_command *cmd, int chld_nb)
{
	pid_t	cpid;
	int		status;
	char **envp_array;
	int builtin_nb;

	builtin_nb = is_builtin(cmd->cmd[0]);
	if (chld_nb == 0 && builtin_nb)
		return (exec_builtin(builtin_nb, cmd, envp));
	cpid = fork();
	if (cpid == -1)
		return (rperror("fork"));
	else if (cpid == 0)
	{
		if (builtin_nb)
			exit(exec_builtin(builtin_nb, cmd, envp)); // using the return value of exec_builtin as return because i don't know how you are handling the returns of the builtins.
		envp_array = env_to_array(*envp);
		if (!envp_array)
			exit(EXIT_FAILURE); // protect all allocations!
		make_exec(cmd, envp_array); // this shouldn't return, if it does, it's an error.
		perror("execve");
		exit(errno);
	}
	waitpid(cpid, &status, 0);
	while (chld_nb--)
		waitpid(-1, NULL, 0);  //this is equal to wait(NULL);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}
