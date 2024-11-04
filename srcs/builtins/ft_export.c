/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:18:07 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/22 15:54:44 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	key_exist(char *key, t_env *envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i].key)
	{
		if (ft_strncmp(envp[i].key, key, len == 0))
			return (1);
		i++;
	}
	return (0);
}

void	free_old_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_env)
	{
		free(shell->envp[i].key);
		free(shell->envp[i].value);
		i++;
	}
	free(shell->envp);
}

void	ft_setenv(char *key, char *value, t_shell *shell)
{
	int		i;
	t_env	*new_env;

	env = malloc(sizeof(t_env));
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	ft_lstadd_back(&envp, ft_lstnew(env));
}

/**
 * ft_export - Adds or updates an environment variable in the shell.
 *
 * @args: A string containing the environment variable and its value in the format "VAR=VALUE".
 * @shell: A pointer to the shell structure containing the environment variables.
* TODO : Handle the case where the environment variable already exists.
* TODO : Handle the case where the key or value are invalid
*/
void	ft_export(char *args, t_shell *shell)
{
	char	**ret;

	if (args)
	{
		ret = ft_split(args, '=');
		if (!ret)
			return ;
		if (!key_exist(ret[0], shell->envp))
		{
			ft_setenv(ret[0], ret[1], shell);
		}
		free(ret[0]);
		free(ret[1]);
		free(ret);
	}
}
