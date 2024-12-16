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

void	ft_override_env(char *key, char *value, t_env **envp)
{
	int	i;

	i = 0;
	while ((*envp)[i].key)
	{
		if (ft_strncmp((*envp)[i].key, key, ft_strlen(key)) == 0)
		{
			if ((*envp)[i].value)
			{
				free((*envp)[i].value);
				(*envp)[i].value = NULL;
			}
			if (value)
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

	nb_env = ft_env_size(*envp);
	new_env = malloc(sizeof(t_env) * (nb_env + 2));
	if (!new_env)
	{
		ft_fprintf(2, "minishell: export: %s\n", strerror(errno));
		return (NULL);
	}
	i = 0;
	while (i < nb_env)
	{
		new_env[i].key = ft_strdup((*envp)[i].key);
		if ((*envp)[i].value)
			new_env[i].value = ft_strdup((*envp)[i].value);
		else
			new_env[i].value = NULL;
		i++;
	}
	new_env[i].key = ft_strdup(key);
	if (value)
		new_env[i].value = ft_strdup(value);
	else
		new_env[i].value = NULL;
	new_env[i + 1].key = NULL;
	new_env[i + 1].value = NULL;
	free_old_env(envp);
	return (new_env);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
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
	char	*key;
	char	*value;
	char	*equal_sign;
	int		i;
	int		status;

	if (!args)
		return (EXIT_FAILURE);
	if (count_char_array(args) == 1)
		return (ft_env(env_to_array(*envp)));
	i = 1;
	status = EXIT_SUCCESS;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			key = args[i];
			value = equal_sign + 1;
			if (!is_valid_identifier(key))
			{
				ft_fprintf(2, "export: '%s': not a valid identifier\n", args[i]);
				status = EXIT_FAILURE;
				i++;
				continue;
			}
			if (!key_exist(key, *envp))
			{
				*envp = ft_setenv(key, value, envp);
			}
			else
				ft_override_env(key, value, envp);
		}
		else
		{
			if (!is_valid_identifier(args[i]))
			{
				ft_fprintf(2, "export: '%s': not a valid identifier\n", args[i]);
				status = EXIT_FAILURE;
			}
		}
		i++;
	}
	return (status);
}