/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:18:07 by stevennke         #+#    #+#             */
/*   Updated: 2025/01/07 17:27:26 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_equal_sign(char *args, char *equal_sign, int *status, t_env **envp)
{
	char	*key;
	char	*value;

	key = args;
	*equal_sign = '\0';
	value = equal_sign + 1;
	if (!is_valid_identifier(key))
	{
		ft_fprintf(2, "export: '%s': not a valid identifier\n", args);
		*status = EXIT_FAILURE;
		return (-1);
	}
	if (!key_exist(key, *envp))
		*envp = ft_setenv(key, value, envp);
	else
		ft_override_env(key, value, envp);
	return (1);
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

void	loop(char **args, int *status, t_env **envp)
{
	char	*equal_sign;
	int		i;

	i = 0;
	while (args[++i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
		{
			if (handle_equal_sign(args[i], equal_sign, status, envp) == -1)
				continue ;
		}
		else
		{
			if (!is_valid_identifier(args[i]))
			{
				ft_fprintf(2, "export: '%s': ", args[i]);
				ft_fprintf(2, "not a valid identifier\n");
				*status = EXIT_FAILURE;
			}
		}
	}
}

int	ft_export(char **args, t_env **envp)
{
	int		status;

	if (!args)
		return (EXIT_FAILURE);
	if (count_char_array(args) == 1)
		return (ft_env(env_to_array(*envp)));
	status = EXIT_SUCCESS;
	loop(args, &status, envp);
	return (status);
}
