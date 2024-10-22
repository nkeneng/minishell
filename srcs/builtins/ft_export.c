/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:18:07 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/22 11:41:52 by snkeneng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int key_exist(char *key,t_list *envp)
{
	t_list *tmp;
	tmp = envp;
	while (tmp)
	{
		if (ft_strncmp(((t_env *)tmp->content)->key, key, ft_strlen(key)) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

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
void	ft_export(char *args, t_shell *shell)
{
	char	**ret;

	if (args)
	{
		ret = ft_split(args, '=');
		if (!ret)
			return ;
		if (key_exist(ret[0], shell->envp))
			return ;
		ft_setenv(ret[0], ret[1], shell->envp);
		free(ret[0]);
		free(ret[1]);
		free(ret);
	}
}
