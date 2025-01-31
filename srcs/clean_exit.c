/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:01:04 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/31 10:46:32 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	clean_exit(int exit_status, t_shell *shell)
{
	if (!shell)
		exit(exit_status);
	if (shell->envp)
		ft_free_envp(shell->envp);
	if (shell->cmds)
		ft_lstclear(shell->cmds, ft_free_command);
	shell->envp = NULL;
	shell->cmds = NULL;
	exit(exit_status);
}
