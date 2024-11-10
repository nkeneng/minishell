/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:16:54 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/10 16:17:49 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*init_shell(char **env)
{
	t_shell	*shell;
	shell = malloc(sizeof(t_shell));
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
