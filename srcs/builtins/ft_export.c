/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:18:07 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/15 15:52:03 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_setenv(char *key, char *value, t_list *envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->key = key;
	env->value = value;
	ft_lstadd_back(&envp, ft_lstnew(env));
}

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
