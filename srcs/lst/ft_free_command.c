/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:39:22 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/23 14:52:41 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_command(void *command)
{
	t_command	*com;

	com = (t_command *) command;
	// free_redirects(command->redirects);
	free_char_array(com->cmd, 0);
	//free redirects
	free(com);
	return ;
}
