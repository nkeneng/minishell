/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:16:54 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/22 11:35:03 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*init_shell(char **env)
{
	t_shell	*shell;
	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (NULL);
	init_envp(env, shell);
	if (!shell->envp)
	{
		free(shell);
		return (NULL);
	}
	return (shell);
}
