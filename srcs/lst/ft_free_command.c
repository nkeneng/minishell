/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:39:22 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/14 18:28:13 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_command(void *command)
{
	t_command	*com;

	com = (t_command *) command;
	// free_redirects(command->redirects);
	free(com->cmd);
	free(com);
	return ;
}
