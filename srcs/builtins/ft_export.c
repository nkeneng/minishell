/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:18:07 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/15 16:39:32 by snkeneng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_setenv(char *key, char *value, t_list *envp)
{
	t_env	*env;

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
*/
void	ft_export(char *args, t_shell *shell)
{
	char	**ret;

	if (args)
	{
		ret = ft_split(args, '=');
		if (!ret)
			return ;
		ft_setenv(ret[0], ret[1], shell->envp);
		free(ret[0]);
		free(ret[1]);
		free(ret);
	}
}
