/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:54:33 by stevennke         #+#    #+#             */
/*   Updated: 2025/01/09 12:29:18 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdarg.h>

void	dummy_cmd_list(t_list **cmd_list, int num_cmds, ...)
{
	va_list		args;
	t_command	*cmd;
	int			i;

	*cmd_list = NULL;
	va_start(args, num_cmds);
	i = 0;
	while (i < num_cmds)
	{
		cmd = ft_calloc(1, sizeof(t_command));
		cmd->cmd = ft_split(va_arg(args, char *), ' ');
		cmd->flags = va_arg(args, int);
		ft_lstadd_back(cmd_list, ft_lstnew(cmd));
		i++;
	}
	va_end(args);
}
