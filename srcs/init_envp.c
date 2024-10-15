/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:51:05 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/15 16:02:39 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_envp(char **env, t_list **envp)
{
	int		i;
	char	**ret;
	t_env	*tmp_env;

	i = 0;
	*envp = NULL;
	tmp_env = malloc(sizeof(t_env));
	while (env[i])
	{
		ret = ft_split(env[i], '=');
		if (!ret || !ret[0] || !ret[1])
			return ;
		// ft_printf("Raw : %s \n Key : %s\n Value : %s\n", env[i], ret[0],
			// ret[1]);
		// i++;
		// continue ;
		tmp_env->key = ft_strdup(ret[0]);
		tmp_env->value = ft_strdup(ret[1]);
		ft_printf("Key : %s\n Value : %s\n", tmp_env->key, tmp_env->value);
		ft_lstadd_back(envp, ft_lstnew(tmp_env));
		i++;
		free(ret[0]);
		free(ret[1]);
		free(ret);
		envp = &(*envp)->next;
	}
}
