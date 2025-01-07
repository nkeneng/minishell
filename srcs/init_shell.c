/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:16:54 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/07 17:34:43 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*init_shell(char **env)
{
	t_shell	*shell;
	init_envp(env, shell);
	if (!shell->envp)
	{
		free(shell);
		return (NULL);
	}
	return (shell);
}
