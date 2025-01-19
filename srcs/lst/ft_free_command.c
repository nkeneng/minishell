/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:39:22 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/19 12:55:33 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_command(void *command)
{
	t_command	*com;

	com = (t_command *) command;
	ft_lstclear(&(com->redirects), ft_free_redirect);
	free_char_array(com->cmd, 0);
	free(com);
	return ;
}
