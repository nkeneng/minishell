/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:07:58 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/31 10:46:02 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO: make this work, it is leaking memory
void	ft_free_shell(t_shell **shell)
{
	if (!shell || !*shell)
		return ;
	if ((*shell)->envp)
		ft_free_envp((*shell)->envp);
	(*shell)->envp = NULL;
}

void	ft_free_envp(t_env *envp)
{
	int	i;

	i = 0;
	while (envp[i].key)
	{
		free(envp[i].key);
		free(envp[i].value);
		i++;
	}
	free(envp);
}
