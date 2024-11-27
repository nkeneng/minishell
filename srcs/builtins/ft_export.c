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
#include <sys/wait.h>
#include <signal.h>

int	key_exist(char *key, t_env *envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i].key)
	{
		if (ft_strncmp(envp[i].key, key , len) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	free_old_env(t_env **envp)
{
	int	i;

	i = 0;

	while ((*envp)[i].key)
	{
		free((*envp)[i].key);
		free((*envp)[i].value);
		i++;
	}
	free(*envp);
}

void ft_override_env(char *key, char *value, t_env **envp)
{
	int	i;

	i = 0;
	while ((*envp)[i].key)
	{
		if (ft_strncmp((*envp[i]).key, key, ft_strlen(key)) == 0)
		{
			free((*envp)[i].value);
			(*envp)[i].value = ft_strdup(value);
			break ;
		}
		i++;
	}
}

t_env	*ft_setenv(char *key, char *value, t_env **envp)
{
	int		i;
	t_env	*new_env;
	int		nb_env;

	i = 0;
	nb_env = ft_env_size(*envp);
	new_env = malloc(sizeof(t_env) * (nb_env + 2));
	if (!new_env)
		return (NULL);
	while (i < nb_env)
	{
		new_env[i].key = ft_strdup((*envp)[i].key);
		new_env[i].value = ft_strdup((*envp)[i].value);
		i++;
	}
	new_env[i].key = ft_strdup(key);
	new_env[i].value = ft_strdup(value);
	new_env[i + 1].key = NULL;
	new_env[i + 1].value = NULL;
	free_old_env(envp);
	return (new_env);
}

/**
 * ft_export - Adds or updates an environment variable in the shell.
 *
 * @args: A string containing the environment variable
 * and its value in the format "VAR=VALUE".
 * @shell: A pointer to the shell structure containing the environment variables.
 * TODO : Handle the case where the key or value are invalid
 */
int	ft_export(char **args, t_env **envp)
{
	char	**ret;
	int		i;

	if (args)
	{
		if (count_char_array(args) == 1)
			return (ft_env(env_to_array(*envp)));
		i = 1;
		while (args[i])
		{
			ret = ft_split(args[i], '=');
			if (!ret)
				return (EXIT_FAILURE);
			if (!ret[0] || (!ft_isalpha(ret[0][0]) && ret[0][0] != '_'))
			{
				ft_printf("export: '%s': not a valid identifier\n", args[i]);
				return (EXIT_FAILURE);
			}
			else
			{
				if (!key_exist(ret[0], *envp))
					*envp = ft_setenv(ret[0], ret[1], envp);
				else
					ft_override_env(ret[0], ret[1], envp);
			}
			free_char_array(ret, 0);
			i++;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
