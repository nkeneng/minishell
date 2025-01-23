/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 08:14:56 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/09 17:58:27 by lmeubrin         ###   ########.fr       */
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

int	exec_builtin(int builtin, t_command *command, t_env **envp, t_shell *shell)
{
	char	**envp_array;
	int		ret;

	(void)shell;
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
	{
		envp_array = env_to_array(*envp);
		ret = ft_env(envp_array);
		free_char_array(envp_array, 0);
		return (ret);
	}
	else if (builtin == EXIT_BUILTIN)
		return (ft_exit(command->cmd, shell));
	return (0);
}
