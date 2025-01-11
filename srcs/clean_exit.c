/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:01:04 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/09 18:02:43 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	clean_exit(int exit_status, t_shell *shell)
{
	if (!shell)
		exit(exit_status);
	if (shell->envp)
		ft_free_envp(shell->envp, shell->nb_env);
	shell->envp = NULL;
	shell->cmds = NULL;
	exit(exit_status);
}
