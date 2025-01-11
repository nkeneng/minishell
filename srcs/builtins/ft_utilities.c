/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:11:21 by admin             #+#    #+#             */
/*   Updated: 2025/01/07 17:25:28 by admin            ###   ########.fr       */
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
		if (ft_strncmp(envp[i].key, key, len) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	fill_new_env(int nb_env, t_env **new_env, t_env **envp)
{
	int	i;

	i = 0;
	while (i < nb_env)
	{
		(*new_env)[i].key = ft_strdup((*envp)[i].key);
		if ((*envp)[i].value)
			(*new_env)[i].value = ft_strdup((*envp)[i].value);
		else
			(*new_env)[i].value = NULL;
		i++;
	}
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
	fill_new_env(nb_env, &new_env, envp);
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
