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

void ft_override_env(char *key, char *value, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_env)
	{
		if (ft_strncmp(shell->envp[i].key, key, ft_strlen(key)) == 0)
		{
			free(shell->envp[i].value);
			shell->envp[i].value = ft_strdup(value);
			break ;
		}
		i++;
	}
}

void	ft_setenv(char *key, char *value, t_shell *shell)
{
	int		i;
	t_env	*new_env;

	i = 0;
	new_env = malloc(sizeof(t_env) * (shell->nb_env + 1));
	while (i < shell->nb_env)
	{
		new_env[i].key = ft_strdup(shell->envp[i].key);
		new_env[i].value = ft_strdup(shell->envp[i].value);
		i++;
	}
	new_env[i].key = ft_strdup(key);
	new_env[i].value = ft_strdup(value);
	free_old_env(shell);
	shell->envp = new_env;
	shell->nb_env++;
}

/**
 * ft_export - Adds or updates an environment variable in the shell.
 *
*
 * @args: A string containing the environment variable
 * and its value in the format "VAR=VALUE".

	* @shell: A pointer to the shell structure containing the environment variables.
 * TODO : Handle the case where the key or value are invalid
 */
void	ft_export(char *args, t_shell *shell)
{
	char	**ret;
	char	**export_args;
	int		i;

	if (args)
	{
		export_args = ft_split(args, ' ');
		if (!export_args)
			return ;
		if (count_char_array(export_args) == 1)
		{
			ft_printf("export: not enough arguments\n");
			free_char_array(export_args, 0);
			return ;
		}
		i = 1;
		while (export_args[i])
		{
			ret = ft_split(export_args[i], '=');
			if (!ret)
				return ;
			if (!key_exist(ret[0], shell->envp))
				ft_setenv(ret[0], ret[1], shell);
			else
				ft_override_env(ret[0], ret[1], shell);
			free(ret[0]);
			free(ret[1]);
			free(ret);
			i++;
		}
	}
}
