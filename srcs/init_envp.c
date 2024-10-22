/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:51:05 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/22 12:37:27 by snkeneng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_envp(char **env, t_list **envp)
{
	int		i;
	char	**ret;
	t_env	*tmp_env;
	t_list *tmp;

	i = 0;
	*envp = NULL;
	(void)tmp;
	while (env[i])
	{
		tmp_env = malloc(sizeof(t_env));
		ret = ft_split(env[i], '=');
		if (!ret) {
			ft_printf("Debug: ret is NULL\n");
			return;
		}
		if (!ret[0]) {
			ft_printf("Debug: ret[0] is NULL\n");
			return;
		}
		if (!ret[1]) {
			ft_printf("Debug: ret[1] is NULL for key %s\n", ret[0]);
			ret[1] = ft_strdup("");
		}
		tmp_env->key = ft_strdup(ret[0]);
		tmp_env->value = ft_strdup(ret[1]);
		ft_lstcreateaddback(envp, tmp_env);
		/* tmp = ft_lstlast(*envp); */
		/* ft_printf("Key : %s\n Value : %s\n", ((t_env *)tmp->content)->key, */
		/* 	((t_env *)tmp->content)->value); */
		i++;
		free(ret[0]);
		free(ret[1]);
		free(ret);
	}
	/* tmp = *envp; */
	/* while(tmp) */
	/* { */
	/* 	ft_printf("Key : %s\n Value : %s\n", ((t_env *)tmp->content)->key, */
	/* 		((t_env *)tmp->content)->value); */
	/* 	tmp = tmp->next; */
	/* } */
}
