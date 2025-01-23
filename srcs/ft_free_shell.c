/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:07:58 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/21 11:27:40 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO: make this work, it is leaking memory
void	ft_free_shell(t_shell **shell)
{
	if (!shell || !*shell)
		return ;
	if ((*shell)->envp)
		ft_free_envp((*shell)->envp, (*shell)->nb_env);
	(*shell)->envp = NULL;
}

void	ft_free_envp(t_env *envp, int nb_env)
{
	int	i;

	i = 0;
	while (i < nb_env)
	{
		free(envp[i].key);
		free(envp[i].value);
		i++;
	}
	free(envp);
}
