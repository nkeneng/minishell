/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:51:05 by stevennke         #+#    #+#             */
/*   Updated: 2024/11/10 16:18:13 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static void copy_values(t_env *envp, char **env)
{
	int i;
	char **ret;
	t_env tmp_env;
	
	i = 0;
	while (env[i])
	{
		ret = ft_split(env[i], '=');
		if (!ret || !ret[0])
			return ;
		if (!ret[1])
			ret[1] = ft_strdup("");
		tmp_env.key = ft_strdup(ret[0]);
		tmp_env.value = ft_strdup(ret[1]);
		envp[i] = tmp_env;
		i++;
		free(ret[0]);
		free(ret[1]);
		free(ret);
	}
	envp[i] = (t_env){NULL, NULL};
}

void	init_envp(char **env, t_shell *shell)
{
	int		i;

	i = get_env_size(env);
	shell->nb_env = i;
	shell->envp = malloc(sizeof(t_env) * (i + 1));
	if (!shell->envp)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	copy_values(shell->envp, env);
}
