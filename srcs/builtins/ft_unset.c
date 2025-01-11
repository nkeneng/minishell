/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:48:49 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/05 12:55:06 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_env_var(t_env **envp, const char *key)
{
	int	j;

	j = 0;
	while ((*envp)[j].key)
	{
		if (ft_strncmp((*envp)[j].key, key, ft_strlen(key)) == 0)
		{
			free((*envp)[j].key);
			free((*envp)[j].value);
			while ((*envp)[j].key)
			{
				(*envp)[j] = (*envp)[j + 1];
				j++;
			}
			break ;
		}
		j++;
	}
}

int	ft_unset(char **args, t_env **envp)
{
	int	i;

	if (!args)
		return (EXIT_FAILURE);
	if (count_char_array(args) == 1)
		return (EXIT_SUCCESS);
	i = 1;
	while (args[i])
	{
		remove_env_var(envp, args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
